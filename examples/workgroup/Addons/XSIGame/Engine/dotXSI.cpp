// dotXSI.cpp: implementation of the dotXSI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "dotXSI.h"
#include "OpenGLDisplay.h"

#include "GameState.h"
char g_szStaticString[MAX_PATH];
CSIBCArray< char >			g_aFirstBone;

#define	WEIGHT_EPS_HIGH	0.999999f
#define WEIGHT_EPS_LOW	0.000001f 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PFNGLCLIENTACTIVETEXTUREARBPROC	glClientActiveTexture = NULL;

char* FixPath (char* in_szString)
{
	SetCurrentDirectory(OpenGLDisplay::m_szRootPath);
	memset ( g_szStaticString,0,MAX_PATH );
	sprintf ( g_szStaticString, "%s\\data\\models\\%s", OpenGLDisplay::m_szRootPath, in_szString );
	return g_szStaticString;
}

dotXSI::dotXSI()
{
	ANIMATIONLENGHT = 29.0f;
	m_iShapeTrack = 0;
	m_fTime = 0.0f;
	m_fFrameRate = ANIMATIONLENGHT;
	UseDotXSIMaterials ( true );
	m_pEnvelope = NULL;
	m_bIsLoaded = false;
	m_bVisible = true;
	m_iCurrentAction = 0;
	m_bUseVertexArray = 0;
	m_lPlaybackFlags = PLAYBACK_DEFAULT;
	m_iPendingAction = -1;

	glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREARBPROC)::wglGetProcAddress("glClientActiveTextureARB");
}	

dotXSI::~dotXSI()
{
	DEBUGENTRY ( "dotXSI::~dotXSI" );

	for (int t=0;t<m_iTextures.GetUsed();t++)
	{
		m_pDisplay->RemoveTexture ( m_iTextures[t] );

	}

	for (int b=0;b<m_BoundingBoxList.GetUsed();b++)
	{
		delete m_BoundingBoxList[b];

	}
	m_BoundingBoxList.DisposeData();

	for (int n=0;n<m_pRenderNodes.GetUsed();n++)
	{
		delete m_pRenderNodes[n];

	}
	m_pRenderNodes.DisposeData();

	

	m_Scene.Close();


}

void dotXSI::Load ( TCHAR*	in_szPath, Display* in_pDisplay)
{
	
	DEBUGENTRY ( "dotXSI::Load" );

	m_pDisplay = in_pDisplay;

	if(m_Scene.Open( FixPath(in_szPath)) == SI_SUCCESS)
	{
		m_Scene.Read();
	}
	else
		return;

	FILE *f = fopen ( "c:\\used.txt", "at");
	if ( f ) fprintf ( f, "%s\n", in_szPath );
	fclose(f);
	//
	// cache render nodes
	//
	FindAllRenderNodes( m_Scene.Root() );

	//
	// cache all fcurves for rapid update later
	//

	FindAllFCurves ( m_Scene.Root() );

	if ( m_AllFCurves.GetUsed() && strcmp ( in_szPath, "hero.xsi") )
	{
		ANIMATIONLENGHT = m_Scene.SceneInfo()->GetEnd();
	}

	//
	// Cache all actions
	//

	FindAllActions ( m_Scene.Root() );

	//
	// Create envelopes
	//

	CreateEnvelopes ();

	BuildBoundingBox ( m_Scene.Root() );

	//
	// load the textures
	//

	CSLImageLibrary *l_pImageLib = m_Scene.GetImageLibrary();

	if ( l_pImageLib )
	{
		for (int i=0;i<l_pImageLib->GetImageCount();i++)
		{
			int l_iID = in_pDisplay->AddTexture (l_pImageLib->GetImageList()[i]->GetSourceFile());

			m_iTextures.Extend(1);
			m_iTextures[m_iTextures.GetUsed()-1] = l_iID;

		}
	}

	m_bIsLoaded = true;
}

void dotXSI::BuildBoundingBox ( CSLModel* in_pModel )
{

	DEBUGENTRY ( "dotXSI::BuildBoundingBox" );

	if ( in_pModel->Primitive() )
	{
		if ( in_pModel->Primitive()->Type() == CSLTemplate::SI_MESH )
		{
			BoundingBox* l_pBB = new BoundingBox;
			m_BoundingBoxList.Extend(1);
			m_BoundingBoxList[m_BoundingBoxList.GetUsed()-1] = l_pBB;

			l_pBB->SetTransform ( in_pModel->Transform() );

			CSLGeometry*	l_pGeo = (CSLGeometry*)in_pModel->Primitive();
			CSLMesh*	l_pMesh = (CSLMesh*)in_pModel->Primitive();
			CSLBaseShape* l_pShape = l_pMesh->Shape();
			CSIBCVector3D* l_PositionList = l_pShape->GetVertexListPtr();
			if ( m_pEnvelope )
			{
				l_PositionList = m_pDestVertex;
			}

			l_pBB->m_pMesh = (CSLMesh*)in_pModel->Primitive();
			l_pBB->m_pMeshVertices = l_PositionList;

			for (int v=0;v<l_pShape->GetVertexCount();v++)
			{
				l_pBB->Grow ( l_PositionList[v]);
			}
		}
	}


	for (int m=0;m<in_pModel->GetChildrenCount();m++)
	{
		BuildBoundingBox ( in_pModel->GetChildrenList()[m] );
	}


}

void dotXSI::FindAllRenderNodes ( CSLModel* in_pModel )
{

	if ( in_pModel->Primitive() )
	{
		if ( in_pModel->Primitive()->Type() == CSLTemplate::SI_MESH )
		{
			in_pModel->Transform()->ComputeLocalMatrix();
			in_pModel->Transform()->ComputeGlobalMatrix();
			RenderNode *l_pNode = new RenderNode;
			l_pNode->m_mMatrix.Set (in_pModel->Transform()->GetGlobalMatrix()); 
			l_pNode->m_pModel = in_pModel;
			l_pNode->m_pShader = NULL;

			if ( !m_pEnvelope && (((CSLGeometry*)in_pModel->Primitive())->ShapeAnimation() == NULL))
			{
				FlattenGeometry ( in_pModel, l_pNode );
			}

			m_pRenderNodes.Extend(1);
			m_pRenderNodes[m_pRenderNodes.GetUsed()-1] = l_pNode;

			//
			// Handle shaders
			//

			CSLBaseMaterial* l_pMat = in_pModel->GlobalMaterial ()->GetMaterial ();

			if ( l_pMat->Type() == CSLTemplate::XSI_MATERIAL )
			{
				//
				// found a shader tree
				//

				l_pNode->m_pShader = GetMaterialSystem()->AddMaterial ( (CSLXSIMaterial*) l_pMat );

			}
		}
	}

	for (int m=0;m<in_pModel->GetChildrenCount();m++)
	{
		FindAllRenderNodes ( in_pModel->GetChildrenList()[m] );
	}

}


void dotXSI::FindAllActions ( CSLModel* in_pModel )
{
	DEBUGENTRY ( "dotXSI::FindAllActions" );

	if ( in_pModel->Mixer() )
	{
		for (int a=0;a<in_pModel->Mixer()->GetActionCount();a++)
		{
			if ( in_pModel->Mixer()->GetActionList()[a]->GetAnimationCount() > 0 )
			{
				CSLAction *l_pCurrentAction = in_pModel->Mixer()->GetActionList()[a];
				
				m_lActionList.Extend(1);
				m_lActionList[m_lActionList.GetUsed()-1] = l_pCurrentAction;

				//
				// connect all parameters
				//
				for (int c=0;c<l_pCurrentAction->GetAnimationCount();c++)
				{
					CSLActionFCurve* l_pFCurve = l_pCurrentAction->GetAnimationList()[c];
					CSLAnimatableType* l_pParam = in_pModel->ParameterFromName ( l_pFCurve->GetParameterXSIPath() );

					if ( l_pParam == NULL )
					{
						//
						// this is bad
						//

						continue;
					}

					l_pFCurve->SetParameter ( l_pParam );


				}

			}
		}

	}

	for (int m=0;m<in_pModel->GetChildrenCount();m++)
	{
		FindAllActions ( in_pModel->GetChildrenList()[m] );
	}



}


void dotXSI::FindAllFCurves ( CSLModel* in_pModel )
{
	DEBUGENTRY ( "dotXSI::FindAllFCurves" );

	if ( in_pModel->Transform() )
	{
		for (int v=0;v<in_pModel->Transform()->GetFCurveCount();v++)
		{
			m_AllFCurves.Extend(1);
			m_AllFCurves[m_AllFCurves.GetUsed()-1] = in_pModel->Transform()->FCurves()[v];

		}
	}

	for (int m=0;m<in_pModel->GetChildrenCount();m++)
	{
		FindAllFCurves ( in_pModel->GetChildrenList()[m] );
	}


}


void dotXSI::Tick ( DWORD milliseconds )
{
	DEBUGENTRY ( "dotXSI::Tick" );

	m_fTime += milliseconds;
	
	int b;
	for (b=0;b<GetBoundingBoxList().GetUsed();b++)
	{
		BoundingBox* l_pBB = GetBoundingBoxList()[b];
		m_bVisible = GetGameState(m_pDisplay)->Cull ( l_pBB );
		l_pBB->m_pMesh->ParentModel()->Visibility()->SetVisibility ( m_bVisible );
	}

	if ( m_lActionList.GetUsed())
	{
		ANIMATIONLENGHT = m_lActionList[m_iCurrentAction ]->GetEndTime() * m_Scene.SceneInfo()->GetFrameRate();
	}
	

	if ( m_fTime > (ANIMATIONLENGHT / m_fFrameRate) * 1000.0f )
	{
		m_fTime = 0.0f;
		if ( m_lPlaybackFlags & PLAYBACK_COMPLETE )
		{
			if ( m_iPendingAction > -1 )
			{
				m_lPlaybackFlags = 0;
				SetCurrentAction ( m_iPendingAction );
			}
		}
	}

	
	for (int f=0;f<m_AllFCurves.GetUsed();f++)
	{
		
		m_AllFCurves[f]->Evaluate ( m_fFrameRate * (m_fTime / 1000.0f)+1 );
	}
	
	if ( m_lActionList.GetUsed())
	{
		int l_aCount = m_lActionList[m_iCurrentAction ]->GetAnimationCount();
		
		for (int c=0;c<l_aCount;c++)
		{
			m_lActionList[m_iCurrentAction]->GetAnimationList()[c]->Evaluate( m_fFrameRate * (m_fTime / 1000.0f)+1 );
		}
	}

	if ( m_bVisible )
	{
		if ( m_pEnvelope )
			TickEnvelope();
	}

	//
	// Transform all bounding boxes
	//

	for (b=0;b<m_BoundingBoxList.GetUsed();b++)
	{
		m_BoundingBoxList[b]->Transform();
	}

	for (int n=0;n<m_pRenderNodes.GetUsed();n++)
		{
			m_pRenderNodes[n]->m_pModel->Transform()->ComputeLocalMatrix();
			m_pRenderNodes[n]->m_pModel->Transform()->ComputeGlobalMatrix();
			m_pRenderNodes[n]->m_mMatrix.Set ( m_pRenderNodes[n]->m_pModel->Transform()->GetGlobalMatrix() );
		}

}
void dotXSI::Render ( )
{
	DEBUGENTRY ( "dotXSI::Render" );

	glEnableClientState ( GL_VERTEX_ARRAY );
	glEnableClientState ( GL_NORMAL_ARRAY );

	for (int n=0;n<m_pRenderNodes.GetUsed();n++)
	{
		bool l_bUsedShaders = false;

		if ( !m_pRenderNodes[n]->m_pModel->Visibility()->GetVisibility() )
		{
			continue;
		}

		//
		// Update transforms 
		//

		glPushMatrix();
		glMultMatrixf ( m_pRenderNodes[n]->m_mMatrix.Raw() );

		CSLGeometry*	l_pGeo = (CSLGeometry*)m_pRenderNodes[n]->m_pModel->Primitive();

		SLIndexedVector3D	*l_pSourceVtx = NULL;
		SLIndexedVector3D	*l_pSourceNormals = NULL;

		if ( ( m_iShapeTrack >= 0 ) && l_pGeo->ShapeAnimation() != NULL )
		{
			CSLShapeAnimation*	l_pShapeAnim = l_pGeo->ShapeAnimation();
			int CurrentFrame = m_fFrameRate * (m_fTime / 1000.0f)+1;

			CSLBaseShape* l_pBaseShape = l_pShapeAnim->Shapes()[CurrentFrame+(m_iShapeTrack*29)];

			l_pSourceVtx = l_pBaseShape->GetIndexedVertexListPtr ();
			l_pSourceNormals = l_pBaseShape->GetIndexedNormalListPtr ();

		}

		CSLMesh*	l_pMesh = (CSLMesh*)m_pRenderNodes[n]->m_pModel->Primitive();
		CSLBaseShape* l_pShape = l_pMesh->Shape();

		CSIBCVector3D* l_PositionList = l_pShape->GetVertexListPtr();
		if ( m_pEnvelope )
		{
			l_PositionList = m_pDestVertex;
		}

		CSIBCVector3D* l_NormalList = l_pShape->GetNormalListPtr();
		CSIBCColorf* l_ColorList = l_pShape->GetColorListPtr();
		CSIBCVector2D*	l_pUV[5];

		l_pUV[0] = NULL;
		int	numUVStages = 0;

		if ( l_pShape->Type() == CSLTemplate::SI_SHAPE )
		{
			CSLShape*	l_p30Shape = (CSLShape*)l_pShape;

			l_pUV[0] = l_p30Shape->GetUVCoordListPtr();
			l_pUV[1] = l_pUV[2] = l_pUV[3] = l_pUV[4] = l_pUV[0];

			numUVStages = 1;

		} else {

			if ( l_pShape->Type() == CSLTemplate::SI_SHAPE35 )
			{
				CSLShape_35*	l_p35Shape = (CSLShape_35*)l_pShape;

				for (int uvCount=0;uvCount<l_p35Shape->GetUVCoordArrayCount();uvCount++)
				{
					CSLUVCoordArray* l_pUVArray = l_p35Shape->UVCoordArrays()[uvCount];

					if ( l_pUVArray != NULL )
					{
						l_pUV[uvCount] = l_pUVArray->GetUVCoordListPtr();
						numUVStages++;

						if ( uvCount == 0 )
						{
							l_pUV[1] = l_pUV[2] = l_pUV[3] = l_pUV[4] = l_pUV[0];
						}
					}

				}

			}
		}

		//
		// draw all triangle lists
		//
		glDisable ( GL_COLOR_MATERIAL );
		if ( m_iUseDotXSIMaterials )
		{
			glEnable ( GL_BLEND );
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		}

		for (int t=0;t<l_pMesh->GetTriangleListCount();t++)
		{
			CSLTriangleList*	l_pTri = l_pMesh->TriangleLists()[t];

			SI_Int*	l_pPos = l_pTri->GetVertexIndicesPtr();
			SI_Int*	l_pNormal = l_pTri->GetNormalIndicesPtr();
			SI_Int*	l_pColor = l_pTri->GetColorIndicesPtr();
			SI_Int* l_pUVindices[5];

			int uvCount;
			for (uvCount = 0;uvCount<l_pTri->GetUVArrayCount();uvCount++)
			{
				l_pUVindices[uvCount] = l_pTri->GetUVIndicesPtr(uvCount);

				if ( uvCount == 0 )
				{
					l_pUVindices[1] = l_pUVindices[2] = l_pUVindices[3] = l_pUVindices[4] = l_pUVindices[0];
				}

			}

			if ( ( m_pRenderNodes[n]->m_pShader == NULL ) || ( !m_pRenderNodes[n]->m_pShader->m_pShaderNodes.GetUsed()))
			{

				CSLBaseMaterial* l_pMat = l_pTri->GetMaterial();
				if ( l_pMat->Type() == CSLTemplate::XSI_MATERIAL )
				{
					if ( m_iUseDotXSIMaterials )
					{
						CSLXSIMaterial*	l_pXSIMat = (CSLXSIMaterial*)l_pMat;

						float*	trans = Find4fParameter (l_pXSIMat, "transparency");
						float alpha = (trans[0] + trans[1] + trans[2]) / 3.0f;

						alpha = 1.0f - alpha;

						if ( alpha < 1.0f )
						{
							glEnable ( GL_BLEND );
							glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
						} else {
							glDisable( GL_BLEND );
						}

						float*	diff = Find4fParameter (l_pXSIMat, "diffuse");
						float spec[] ={ 0.0f, 0.0f, 0.0f, 0.0f };

						diff[3] = alpha;
						glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, diff);					
						glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, Find4fParameter (l_pXSIMat, "ambient"));
						glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, spec);
						glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS , 0);
					}

					if ( m_iTextures.GetUsed())
					{
						glEnable ( GL_TEXTURE_2D );
						glBindTexture(GL_TEXTURE_2D,m_iTextures[0]);
					} else {
						glDisable( GL_TEXTURE_2D );
					}

				}
			} else {

				//
				// use shaders

				glDisable( GL_BLEND );
				l_bUsedShaders = true;
				
				numUVStages = GetMaterialSystem()->ExecuteShader ( m_pRenderNodes[n]->m_pShader );
				if ( !numUVStages )
					glDisable ( GL_TEXTURE_2D );

			}

			if ( l_pSourceVtx == NULL )	// non-shapeanimated models
			{
				LONG s = (LONG)&m_pRenderNodes[n]->m_pGeometry[1].x;
				s -= (LONG)&m_pRenderNodes[n]->m_pGeometry[0].x;
				glVertexPointer ( 3, GL_FLOAT, s, &m_pRenderNodes[n]->m_pGeometry[0].x );
				glNormalPointer ( GL_FLOAT, s, &m_pRenderNodes[n]->m_pGeometry[0].nx );
				
				if ( m_pRenderNodes[n]->m_bUseColor )
				{
					glEnableClientState ( GL_COLOR_ARRAY );
					glColorPointer ( 4, GL_FLOAT, s, &m_pRenderNodes[n]->m_pGeometry[0].r );
				} else {
					glDisableClientState ( GL_COLOR_ARRAY );
				}

				for (int v=0;v<5;v++)
				{
					if ( glClientActiveTexture )
						glClientActiveTexture ( GL_TEXTURE0_ARB + v );

					glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
				}

				int curUVStage = 0;
				for (int u=0;u<numUVStages;u++)
				{
					if ( glClientActiveTexture )
						glClientActiveTexture ( GL_TEXTURE0_ARB + u );

					glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
					glTexCoordPointer (2, GL_FLOAT, s, &m_pRenderNodes[n]->m_pGeometry[0].uv[curUVStage][0] );

					curUVStage++;
					if ( curUVStage >= m_pRenderNodes[n]->m_iNbUvs )
					{
						curUVStage = m_pRenderNodes[n]->m_iNbUvs-1;
					}

				}
				
				glDrawArrays ( GL_TRIANGLES, 0, m_pRenderNodes[n]->m_lNBVertex );


			} else {

				glBegin ( GL_TRIANGLES );
				for (int i=0;i<l_pTri->GetTriangleCount();i++)
				{

					for (uvCount=0;uvCount<numUVStages;uvCount++)
					{
						CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
						SI_Int*			l_uvindices = l_pUVindices[uvCount];

						m_pDisplay->MultiTexCoord ( uvCount, 
							l_uvarray[l_uvindices[i*3]].GetX(), 
							l_uvarray[l_uvindices[(i*3)]].GetY() );
					}

					glNormal3f ( l_pSourceNormals[l_pNormal[i*3]].m_Vector3D.GetX(), l_pSourceNormals[l_pNormal[(i*3)]].m_Vector3D.GetY(), l_pSourceNormals[l_pNormal[(i*3)]].m_Vector3D.GetZ() );
					glVertex3f ( l_pSourceVtx[l_pPos[i*3]].m_Vector3D.GetX(), l_pSourceVtx[l_pPos[(i*3)]].m_Vector3D.GetY(), l_pSourceVtx[l_pPos[(i*3)]].m_Vector3D.GetZ() );

					for ( uvCount=0;uvCount<numUVStages;uvCount++)
					{
						CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
						SI_Int*			l_uvindices = l_pUVindices[uvCount];

						m_pDisplay->MultiTexCoord ( uvCount, 
							l_uvarray[l_uvindices[(i*3)+1]].GetX(),
							l_uvarray[l_uvindices[((i*3)+1)]].GetY() );

					}

					glNormal3f ( l_pSourceNormals[l_pNormal[(i*3)+1]].m_Vector3D.GetX(), l_pSourceNormals[l_pNormal[((i*3)+1)]].m_Vector3D.GetY(), l_pSourceNormals[l_pNormal[((i*3)+1)]].m_Vector3D.GetZ() );
					glVertex3f ( l_pSourceVtx[l_pPos[(i*3)+1]].m_Vector3D.GetX(), l_pSourceVtx[l_pPos[((i*3)+1)]].m_Vector3D.GetY(), l_pSourceVtx[l_pPos[((i*3)+1)]].m_Vector3D.GetZ() );


					for ( uvCount=0;uvCount<numUVStages;uvCount++)
					{
						CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
						SI_Int*			l_uvindices = l_pUVindices[uvCount];

						m_pDisplay->MultiTexCoord ( uvCount, 
							l_uvarray[l_uvindices[(i*3)+2]].GetX(), 
							l_uvarray[l_uvindices[((i*3)+2)]].GetY() );

					}

					glNormal3f ( l_pSourceNormals[l_pNormal[(i*3)+2]].m_Vector3D.GetX(), l_pSourceNormals[l_pNormal[((i*3)+2)]].m_Vector3D.GetY(), l_pSourceNormals[l_pNormal[((i*3)+2)]].m_Vector3D.GetZ() );
					glVertex3f ( l_pSourceVtx[l_pPos[(i*3)+2]].m_Vector3D.GetX(), l_pSourceVtx[l_pPos[((i*3)+2)]].m_Vector3D.GetY(), l_pSourceVtx[l_pPos[((i*3)+2)]].m_Vector3D.GetZ() );



				}
				glEnd();
			}


		}

		glPopMatrix();

		if ( l_bUsedShaders )
		{
			//
			// turn them off now.
			//

			GetMaterialSystem()->ShutdownShader ( m_pRenderNodes[n]->m_pShader );

		}

	}

	if ( glClientActiveTexture)
		glClientActiveTexture ( GL_TEXTURE0_ARB );

	glDisableClientState ( GL_VERTEX_ARRAY );
	glDisableClientState ( GL_NORMAL_ARRAY );
}

bool dotXSI::TestCollision (dotXSI* in_pCollider, CSIBCVector3D& out_Collision)
{
	
	DEBUGENTRY ( "dotXSI::TestCollision" );
	
	CSIBCArray<BoundingBox*>& bblist = in_pCollider->GetBoundingBoxList ();
	
	for (int v=0;v<bblist.GetUsed();v++)
		for (int i=0;i<m_BoundingBoxList.GetUsed();i++)
		{
			bool collide = false;

			collide = bblist[v]->TestCollision ( m_BoundingBoxList[i], out_Collision);

			if ( collide )
				return true;
		}

	return false;


}


void dotXSI::RecursiveModelRender ( CSLModel* in_pModel )
{
	DEBUGENTRY ( "dotXSI::RecursiveModelRender" );

	glPushMatrix();

	if ( in_pModel->Transform() )
	{
		in_pModel->Transform()->ComputeLocalMatrix();
		glMultMatrixf ( in_pModel->Transform()->GetMatrix().Raw() );
	}

	if ( in_pModel->Primitive() )
	{
		if ( in_pModel->Primitive()->Type() == CSLTemplate::SI_MESH )
		{
			CSLGeometry*	l_pGeo = (CSLGeometry*)in_pModel->Primitive();

			SLIndexedVector3D	*l_pSourceVtx = NULL;
			SLIndexedVector3D	*l_pSourceNormals = NULL;

			if ( ( m_iShapeTrack >= 0 ) && l_pGeo->ShapeAnimation() != NULL )
			{
				CSLShapeAnimation*	l_pShapeAnim = l_pGeo->ShapeAnimation();
				int CurrentFrame = m_fFrameRate * (m_fTime / 1000.0f)+1;
//				char mess[256];
//				sprintf ( mess,"currentframe:%d\n",CurrentFrame+(m_iShapeTrack*29) );
//				OutputDebugString ( mess );

				CSLBaseShape* l_pBaseShape = l_pShapeAnim->Shapes()[CurrentFrame+(m_iShapeTrack*29)];
								
				l_pSourceVtx = l_pBaseShape->GetIndexedVertexListPtr ();
				l_pSourceNormals = l_pBaseShape->GetIndexedNormalListPtr ();

			}

			CSLMesh*	l_pMesh = (CSLMesh*)in_pModel->Primitive();
			CSLBaseShape* l_pShape = l_pMesh->Shape();

			CSIBCVector3D* l_PositionList = l_pShape->GetVertexListPtr();
			if ( m_pEnvelope )
			{
				l_PositionList = m_pDestVertex;
			}

			CSIBCVector3D* l_NormalList = l_pShape->GetNormalListPtr();
			CSIBCVector2D*	l_pUV[8];

			l_pUV[0] = NULL;
			int	numUVStages = 0;

			if ( l_pShape->Type() == CSLTemplate::SI_SHAPE )
			{
				CSLShape*	l_p30Shape = (CSLShape*)l_pShape;
				
				l_pUV[0] = l_p30Shape->GetUVCoordListPtr();
				numUVStages = 1;
				
			} else {
				
				if ( l_pShape->Type() == CSLTemplate::SI_SHAPE35 )
				{
					CSLShape_35*	l_p35Shape = (CSLShape_35*)l_pShape;
					
					for (int uvCount=0;uvCount<l_p35Shape->GetUVCoordArrayCount();uvCount++)
					{

						CSLUVCoordArray* l_pUVArray = l_p35Shape->UVCoordArrays()[uvCount];
						
						if ( l_pUVArray != NULL )
						{
							l_pUV[uvCount] = l_pUVArray->GetUVCoordListPtr();
							numUVStages++;
						}
						
					}
					
				}
			}

			//
			// draw all triangle lists
			//

			if ( m_iUseDotXSIMaterials )
			{
				glEnable ( GL_BLEND );
				glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			}

			for (int t=0;t<l_pMesh->GetTriangleListCount();t++)
			{
				CSLTriangleList*	l_pTri = l_pMesh->TriangleLists()[t];

				SI_Int*	l_pPos = l_pTri->GetVertexIndicesPtr();
				SI_Int*	l_pNormal = l_pTri->GetNormalIndicesPtr();

				SI_Int* l_pUVindices[8];

				int uvCount;
				for (uvCount = 0;uvCount<l_pTri->GetUVArrayCount();uvCount++)
				{
					l_pUVindices[uvCount] = l_pTri->GetUVIndicesPtr(uvCount);
				}

				CSLBaseMaterial* l_pMat = l_pTri->GetMaterial();
				if ( l_pMat->Type() == CSLTemplate::XSI_MATERIAL )
				{
					if ( m_iUseDotXSIMaterials )
					{
						CSLXSIMaterial*	l_pXSIMat = (CSLXSIMaterial*)l_pMat;

						float*	trans = Find4fParameter (l_pXSIMat, "transparency");
						float alpha = (trans[0] + trans[1] + trans[2]) / 3.0f;
						
						alpha = 1.0f - alpha;

						if ( alpha < 1.0f )
						{
							glEnable ( GL_BLEND );
							glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
						} else {
							glDisable( GL_BLEND );
						}

						float*	diff = Find4fParameter (l_pXSIMat, "diffuse");
						float spec[] ={ 0.0f, 0.0f, 0.0f, 0.0f };

						diff[3] = alpha;
						glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, diff);					
						glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, Find4fParameter (l_pXSIMat, "ambient"));
						glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, spec);
						glMaterialf ( GL_FRONT_AND_BACK, GL_SHININESS , 0);
					}

					if ( m_iTextures.GetUsed())
					{
						glEnable ( GL_TEXTURE_2D );
						glBindTexture(GL_TEXTURE_2D,m_iTextures[0]);
					} else {
						glDisable( GL_TEXTURE_2D );
					}

				}

				if ( l_pSourceVtx == NULL )	// non-shapeanimated models
				{

					glBegin ( GL_TRIANGLES );
					for (int i=0;i<l_pTri->GetTriangleCount();i++)
					{
						int uvCount;
						
						for (uvCount=0;uvCount<numUVStages;uvCount++)
						{
							CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
							SI_Int*			l_uvindices = l_pUVindices[uvCount];
							
							m_pDisplay->MultiTexCoord ( uvCount, 
								l_uvarray[l_uvindices[i*3]].GetX(), 
								l_uvarray[l_uvindices[(i*3)]].GetY() );
						}
						
						glNormal3f ( l_NormalList[l_pNormal[i*3]].GetX(), l_NormalList[l_pNormal[(i*3)]].GetY(), l_NormalList[l_pNormal[(i*3)]].GetZ() );
						glVertex3f ( l_PositionList[l_pPos[i*3]].GetX(), l_PositionList[l_pPos[(i*3)]].GetY(), l_PositionList[l_pPos[(i*3)]].GetZ() );
						
						for ( uvCount=0;uvCount<numUVStages;uvCount++)
						{
							CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
							SI_Int*			l_uvindices = l_pUVindices[uvCount];
							
							m_pDisplay->MultiTexCoord ( uvCount, 
								l_uvarray[l_uvindices[(i*3)+1]].GetX(),
								l_uvarray[l_uvindices[((i*3)+1)]].GetY() );
							
						}
						
						glNormal3f ( l_NormalList[l_pNormal[(i*3)+1]].GetX(), l_NormalList[l_pNormal[((i*3)+1)]].GetY(), l_NormalList[l_pNormal[((i*3)+1)]].GetZ() );
						glVertex3f ( l_PositionList[l_pPos[(i*3)+1]].GetX(), l_PositionList[l_pPos[((i*3)+1)]].GetY(), l_PositionList[l_pPos[((i*3)+1)]].GetZ() );
						
						for ( uvCount=0;uvCount<numUVStages;uvCount++)
						{
							CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
							SI_Int*			l_uvindices = l_pUVindices[uvCount];
							
							m_pDisplay->MultiTexCoord ( uvCount, 
								l_uvarray[l_uvindices[(i*3)+2]].GetX(), 
								l_uvarray[l_uvindices[((i*3)+2)]].GetY() );
							
						}
						
						glNormal3f ( l_NormalList[l_pNormal[(i*3)+2]].GetX(), l_NormalList[l_pNormal[((i*3)+2)]].GetY(), l_NormalList[l_pNormal[((i*3)+2)]].GetZ() );
						glVertex3f ( l_PositionList[l_pPos[(i*3)+2]].GetX(), l_PositionList[l_pPos[((i*3)+2)]].GetY(), l_PositionList[l_pPos[((i*3)+2)]].GetZ() );
						
						
						
					}
					glEnd();

				} else {

					glBegin ( GL_TRIANGLES );
					for (int i=0;i<l_pTri->GetTriangleCount();i++)
					{
						
						for (uvCount=0;uvCount<numUVStages;uvCount++)
						{
							CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
							SI_Int*			l_uvindices = l_pUVindices[uvCount];
							
							m_pDisplay->MultiTexCoord ( uvCount, 
								l_uvarray[l_uvindices[i*3]].GetX(), 
								l_uvarray[l_uvindices[(i*3)]].GetY() );
						}
						
						glNormal3f ( l_pSourceNormals[l_pNormal[i*3]].m_Vector3D.GetX(), l_pSourceNormals[l_pNormal[(i*3)]].m_Vector3D.GetY(), l_pSourceNormals[l_pNormal[(i*3)]].m_Vector3D.GetZ() );
						glVertex3f ( l_pSourceVtx[l_pPos[i*3]].m_Vector3D.GetX(), l_pSourceVtx[l_pPos[(i*3)]].m_Vector3D.GetY(), l_pSourceVtx[l_pPos[(i*3)]].m_Vector3D.GetZ() );
						
						for ( uvCount=0;uvCount<numUVStages;uvCount++)
						{
							CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
							SI_Int*			l_uvindices = l_pUVindices[uvCount];
							
							m_pDisplay->MultiTexCoord ( uvCount, 
								l_uvarray[l_uvindices[(i*3)+1]].GetX(),
								l_uvarray[l_uvindices[((i*3)+1)]].GetY() );
							
						}
						
						glNormal3f ( l_pSourceNormals[l_pNormal[(i*3)+1]].m_Vector3D.GetX(), l_pSourceNormals[l_pNormal[((i*3)+1)]].m_Vector3D.GetY(), l_pSourceNormals[l_pNormal[((i*3)+1)]].m_Vector3D.GetZ() );
						glVertex3f ( l_pSourceVtx[l_pPos[(i*3)+1]].m_Vector3D.GetX(), l_pSourceVtx[l_pPos[((i*3)+1)]].m_Vector3D.GetY(), l_pSourceVtx[l_pPos[((i*3)+1)]].m_Vector3D.GetZ() );
						
						
						for ( uvCount=0;uvCount<numUVStages;uvCount++)
						{
							CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
							SI_Int*			l_uvindices = l_pUVindices[uvCount];
							
							m_pDisplay->MultiTexCoord ( uvCount, 
								l_uvarray[l_uvindices[(i*3)+2]].GetX(), 
								l_uvarray[l_uvindices[((i*3)+2)]].GetY() );
							
						}
						
						glNormal3f ( l_pSourceNormals[l_pNormal[(i*3)+2]].m_Vector3D.GetX(), l_pSourceNormals[l_pNormal[((i*3)+2)]].m_Vector3D.GetY(), l_pSourceNormals[l_pNormal[((i*3)+2)]].m_Vector3D.GetZ() );
						glVertex3f ( l_pSourceVtx[l_pPos[(i*3)+2]].m_Vector3D.GetX(), l_pSourceVtx[l_pPos[((i*3)+2)]].m_Vector3D.GetY(), l_pSourceVtx[l_pPos[((i*3)+2)]].m_Vector3D.GetZ() );
						
						
						
					}
					glEnd();
				}


			}

		}
	}

	for (int m=0;m<in_pModel->GetChildrenCount();m++)
	{
		RecursiveModelRender ( in_pModel->GetChildrenList()[m] );
	}

	glPopMatrix();
}

void dotXSI::RecursiveModelRenderVA ( CSLModel* in_pModel )
{
		glPushMatrix();

	if ( in_pModel->Transform() )
	{
		in_pModel->Transform()->ComputeLocalMatrix();
		glMultMatrixf ( in_pModel->Transform()->GetMatrix().Raw() );
	}

	if ( in_pModel->Primitive() )
	{
		if ( in_pModel->Primitive()->Type() == CSLTemplate::SI_MESH )
		{
			CSLMesh*	l_pMesh = (CSLMesh*)in_pModel->Primitive();
			CSLBaseShape* l_pShape = l_pMesh->Shape();

			CSIBCVector3D* l_PositionList = l_pShape->GetVertexListPtr();
			if ( m_pEnvelope )
			{
				l_PositionList = m_pDestVertex;
			}
			CSIBCVector3D* l_NormalList = l_pShape->GetNormalListPtr();
			CSIBCVector2D*	l_pUV = NULL;

			if ( l_pShape->Type() == CSLTemplate::SI_SHAPE )
			{
				CSLShape*	l_p30Shape = (CSLShape*)l_pShape;
				
				l_pUV = l_p30Shape->GetUVCoordListPtr();
				
			} else {
				
				if ( l_pShape->Type() == CSLTemplate::SI_SHAPE35 )
				{
					CSLShape_35*	l_p35Shape = (CSLShape_35*)l_pShape;
					
					if ( l_p35Shape->GetUVCoordArrayCount() )
					{
						CSLUVCoordArray* l_pUVArray = l_p35Shape->UVCoordArrays()[0];
						
						if ( l_pUVArray != NULL )
						{
							l_pUV = l_pUVArray->GetUVCoordListPtr();
						}
						
					}
					
				}
			}

			glEnableClientState ( GL_NORMAL_ARRAY  );
			glEnableClientState ( GL_VERTEX_ARRAY  );

			LONG striden = (LONG)(&l_NormalList[1].m_fX) - (LONG)(&l_NormalList[0].m_fX) ;
			LONG stridep = (LONG)(&l_PositionList[1].m_fX) - (LONG)(&l_PositionList[0].m_fX) ;
			glNormalPointer (GL_FLOAT, 0,(void*)&l_NormalList[0].m_fX );
			glVertexPointer ( 3, GL_FLOAT, stridep,(void*)&l_PositionList[0].m_fX );

			//
			// draw all triangle lists
			//

			glEnable ( GL_BLEND );
			glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

			for (int t=0;t<l_pMesh->GetTriangleListCount();t++)
			{
				CSLTriangleList*	l_pTri = l_pMesh->TriangleLists()[t];

				SI_Int*	l_pPos = l_pTri->GetVertexIndicesPtr();
				SI_Int*	l_pNormal = l_pTri->GetNormalIndicesPtr();
				SI_Int* l_pUVindices = l_pTri->GetUVIndicesPtr(0);

				CSLBaseMaterial* l_pMat = l_pTri->GetMaterial();
				if ( l_pMat->Type() == CSLTemplate::XSI_MATERIAL )
				{
					CSLXSIMaterial*	l_pXSIMat = (CSLXSIMaterial*)l_pMat;

					float*	trans = Find4fParameter (l_pXSIMat, "transparency");
					float alpha = (trans[0] + trans[1] + trans[2]) / 3.0f;
					
					alpha = 1.0f - alpha;

					float*	diff = Find4fParameter (l_pXSIMat, "diffuse");
					diff[3] = alpha;
					glMaterialfv ( GL_FRONT_AND_BACK, GL_DIFFUSE, diff);					
					glMaterialfv ( GL_FRONT_AND_BACK, GL_AMBIENT, Find4fParameter (l_pXSIMat, "ambient"));
				//	glMaterialfv ( GL_FRONT_AND_BACK, GL_SPECULAR, Find4fParameter (l_pXSIMat, "specular"));
				}


//				glIndexPointer ( GL_INT, 0, &l_pPos[0] );

//				glDrawArrays ( GL_TRIANGLES, 0, l_pTri->GetTriangleCount() * 3);
				glDrawElements(GL_TRIANGLES,l_pTri->GetTriangleCount() * 3,GL_INT,&l_pPos[0]);
				
/*
				glBegin ( GL_TRIANGLES );
				for (int i=0;i<l_pTri->GetTriangleCount();i++)
				{
					if ( l_pUV )
						glTexCoord2d ( l_pUV[l_pUVindices[i*3]].GetX(), l_pUV[l_pUVindices[(i*3)]].GetY() );

						glNormal3f ( l_NormalList[l_pNormal[i*3]].GetX(), l_NormalList[l_pNormal[(i*3)]].GetY(), l_NormalList[l_pNormal[(i*3)]].GetZ() );
						glVertex3f ( l_PositionList[l_pPos[i*3]].GetX(), l_PositionList[l_pPos[(i*3)]].GetY(), l_PositionList[l_pPos[(i*3)]].GetZ() );

					if ( l_pUV )
						glTexCoord2d ( l_pUV[l_pUVindices[(i*3)+1]].GetX(), l_pUV[l_pUVindices[((i*3)+1)]].GetY() );

						glNormal3f ( l_NormalList[l_pNormal[(i*3)+1]].GetX(), l_NormalList[l_pNormal[((i*3)+1)]].GetY(), l_NormalList[l_pNormal[((i*3)+1)]].GetZ() );
						glVertex3f ( l_PositionList[l_pPos[(i*3)+1]].GetX(), l_PositionList[l_pPos[((i*3)+1)]].GetY(), l_PositionList[l_pPos[((i*3)+1)]].GetZ() );

					if ( l_pUV )
						glTexCoord2d ( l_pUV[l_pUVindices[(i*3)+2]].GetX(), l_pUV[l_pUVindices[((i*3)+2)]].GetY() );
					
						glNormal3f ( l_NormalList[l_pNormal[(i*3)+2]].GetX(), l_NormalList[l_pNormal[((i*3)+2)]].GetY(), l_NormalList[l_pNormal[((i*3)+2)]].GetZ() );
						glVertex3f ( l_PositionList[l_pPos[(i*3)+2]].GetX(), l_PositionList[l_pPos[((i*3)+2)]].GetY(), l_PositionList[l_pPos[((i*3)+2)]].GetZ() );



				}
				glEnd();
*/

		
			}
			
			glDisable( GL_NORMAL_ARRAY  );
			glDisable( GL_VERTEX_ARRAY  );

		}
	}

	for (int m=0;m<in_pModel->GetChildrenCount();m++)
	{
		RecursiveModelRenderVA ( in_pModel->GetChildrenList()[m] );
	}

	glPopMatrix();

}


void dotXSI::RenderUsingVertexArrays ( DWORD milliseconds )
{
	RecursiveModelRenderVA ( m_Scene.Root() );
}


float* dotXSI::Find4fParameter ( CSLXSIMaterial* in_pMat, char* in_szParamName)
{
	DEBUGENTRY ( "dotXSI::Find4fParameter" );

	tParams[0] = tParams[1] = tParams[2] = tParams[3] = 0.0f;

	for (int s=0;s<in_pMat->GetShaderCount();s++)
	{
		CSLXSIShader*	l_pShader = in_pMat->GetShaderList()[s];

		for (int p=0;p<l_pShader->GetParameterCount();p++)
		{
			if (strstr ( l_pShader->GetParameterList()[p]->GetName(), in_szParamName ))
			{
					tParams[0] = l_pShader->GetParameterList()[p]->GetValue()->fVal;
					tParams[1] = l_pShader->GetParameterList()[p+1]->GetValue()->fVal;
					tParams[2] = l_pShader->GetParameterList()[p+2]->GetValue()->fVal;
					tParams[3] = l_pShader->GetParameterList()[p+3]->GetValue()->fVal;
					return tParams;
			}

		}

	}

	return tParams;
}

LONG dotXSI::Find1lParameter( CSLXSIMaterial* in_pMat, char* in_szParamName )
{
	DEBUGENTRY ( "dotXSI::Find1lParameter" );

	LONG retval = 0;

	for (int s=0;s<in_pMat->GetShaderCount();s++)
	{
		CSLXSIShader*	l_pShader = in_pMat->GetShaderList()[s];

		for (int p=0;p<l_pShader->GetParameterCount();p++)
		{
			if (strstr ( l_pShader->GetParameterList()[p]->GetName(), in_szParamName))
			{
				TinyVariant*	l_pvar = l_pShader->GetParameterList()[p]->GetValue();

					retval = l_pShader->GetParameterList()[p]->GetValue()->bVal;
					return retval;
			}

		}

	}

	return retval;
}


void dotXSI::RenderBoundingBoxList ()
{
	DEBUGENTRY ( "dotXSI::RenderBoundingBoxList" );

	//
	// render all bb
	//
	

	glPushAttrib ( GL_ALL_ATTRIB_BITS );
	glDisable ( GL_LIGHTING );
	glDisable ( GL_TEXTURE_2D );
	
	for (int b=0;b<m_BoundingBoxList.GetUsed();b++)
	{
		CSIBCVector3D max_xform;
		CSIBCVector3D min_xform;
		
		m_BoundingBoxList[b]->GetXFormAABB( max_xform, min_xform );
		
		float edge1 = (float)fabs(max_xform.m_fX - min_xform.m_fX) / 3.0f;
		float edge2 = (float)fabs(max_xform.m_fZ - min_xform.m_fZ) / 3.0f;
		float edge3 = (float)fabs(max_xform.m_fY - min_xform.m_fY) / 3.0f;
		


		glColor3f(0.0f,0.0f,1.0f);
		
		glBegin(GL_LINES);
		glVertex3f(max_xform.m_fX,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX-edge1,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX,max_xform.m_fY,max_xform.m_fZ-edge2 );
		glVertex3f(max_xform.m_fX,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX,max_xform.m_fY-edge3,max_xform.m_fZ);
		
		glVertex3f(min_xform.m_fX,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX+edge1,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX,max_xform.m_fY,max_xform.m_fZ-edge2 );
		glVertex3f(min_xform.m_fX,max_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX,max_xform.m_fY-edge3,max_xform.m_fZ);
		
		glVertex3f(min_xform.m_fX,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX+edge1,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX,min_xform.m_fY,max_xform.m_fZ-edge2 );
		glVertex3f(min_xform.m_fX,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(min_xform.m_fX,min_xform.m_fY+edge3,max_xform.m_fZ);
		
		glVertex3f(min_xform.m_fX,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX+edge1,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX,min_xform.m_fY,min_xform.m_fZ+edge2 );
		glVertex3f(min_xform.m_fX,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX,min_xform.m_fY+edge3,min_xform.m_fZ);
		
		glVertex3f(min_xform.m_fX,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX+edge1,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX,max_xform.m_fY,min_xform.m_fZ+edge2 );
		glVertex3f(min_xform.m_fX,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(min_xform.m_fX,max_xform.m_fY-edge3,min_xform.m_fZ);
		
		glVertex3f(max_xform.m_fX,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX-edge1,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX,max_xform.m_fY,min_xform.m_fZ+edge2 );
		glVertex3f(max_xform.m_fX,max_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX,max_xform.m_fY-edge3,min_xform.m_fZ);
		
		glVertex3f(max_xform.m_fX,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX-edge1,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX,min_xform.m_fY,max_xform.m_fZ-edge2 );
		glVertex3f(max_xform.m_fX,min_xform.m_fY,max_xform.m_fZ );
		glVertex3f(max_xform.m_fX,min_xform.m_fY+edge3,max_xform.m_fZ);
		
		glVertex3f(max_xform.m_fX,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX-edge1,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX,min_xform.m_fY,min_xform.m_fZ+edge2 );
		glVertex3f(max_xform.m_fX,min_xform.m_fY,min_xform.m_fZ );
		glVertex3f(max_xform.m_fX,min_xform.m_fY+edge3,min_xform.m_fZ);
		
		glEnd();



		glColor3f(1.0f,1.0f,1.0f);

		glBegin ( GL_POINTS );
		for (int p=6;p<7;p++)
			glVertex3f ( m_BoundingBoxList[b]->bc[p].m_fX,
							m_BoundingBoxList[b]->bc[p].m_fY,
							m_BoundingBoxList[b]->bc[p].m_fZ);
		glEnd();
/*
		glBegin ( GL_TRIANGLES );

		// 0,1,2
		glVertex3f ( m_BoundingBoxList[b]->bc[0].m_fX,
						m_BoundingBoxList[b]->bc[0].m_fY,
						m_BoundingBoxList[b]->bc[0].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[1].m_fX,
						m_BoundingBoxList[b]->bc[1].m_fY,
						m_BoundingBoxList[b]->bc[1].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[2].m_fX,
						m_BoundingBoxList[b]->bc[2].m_fY,
						m_BoundingBoxList[b]->bc[2].m_fZ);
		// 0,1,3
		glVertex3f ( m_BoundingBoxList[b]->bc[0].m_fX,
						m_BoundingBoxList[b]->bc[0].m_fY,
						m_BoundingBoxList[b]->bc[0].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[1].m_fX,
						m_BoundingBoxList[b]->bc[1].m_fY,
						m_BoundingBoxList[b]->bc[1].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[3].m_fX,
						m_BoundingBoxList[b]->bc[3].m_fY,
						m_BoundingBoxList[b]->bc[3].m_fZ);

		glVertex3f ( m_BoundingBoxList[b]->bc[3].m_fX,
						m_BoundingBoxList[b]->bc[3].m_fY,
						m_BoundingBoxList[b]->bc[3].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[0].m_fX,
						m_BoundingBoxList[b]->bc[0].m_fY,
						m_BoundingBoxList[b]->bc[0].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[6].m_fX,
						m_BoundingBoxList[b]->bc[6].m_fY,
						m_BoundingBoxList[b]->bc[6].m_fZ);


		glVertex3f ( m_BoundingBoxList[b]->bc[3].m_fX,
						m_BoundingBoxList[b]->bc[3].m_fY,
						m_BoundingBoxList[b]->bc[3].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[6].m_fX,
						m_BoundingBoxList[b]->bc[6].m_fY,
						m_BoundingBoxList[b]->bc[6].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[4].m_fX,
					m_BoundingBoxList[b]->bc[4].m_fY,
					m_BoundingBoxList[b]->bc[4].m_fZ);

		glVertex3f ( m_BoundingBoxList[b]->bc[4].m_fX,
						m_BoundingBoxList[b]->bc[4].m_fY,
						m_BoundingBoxList[b]->bc[4].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[6].m_fX,
						m_BoundingBoxList[b]->bc[6].m_fY,
						m_BoundingBoxList[b]->bc[6].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[5].m_fX,
					m_BoundingBoxList[b]->bc[5].m_fY,
					m_BoundingBoxList[b]->bc[5].m_fZ);


		glVertex3f ( m_BoundingBoxList[b]->bc[4].m_fX,
						m_BoundingBoxList[b]->bc[4].m_fY,
						m_BoundingBoxList[b]->bc[4].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[5].m_fX,
						m_BoundingBoxList[b]->bc[5].m_fY,
						m_BoundingBoxList[b]->bc[5].m_fZ);
		glVertex3f ( m_BoundingBoxList[b]->bc[0].m_fX,
					m_BoundingBoxList[b]->bc[0].m_fY,
					m_BoundingBoxList[b]->bc[0].m_fZ);


		glEnd();
*/
		//glBegin(GL_LINES);
		//glVertex3f(max_xform.m_fX,max_xform.m_fY,max_xform.m_fZ );
		//glVertex3f(min_xform.m_fX,min_xform.m_fY,min_xform.m_fZ );
		//glEnd();
	
		
	}
	
	glPopAttrib();

	

}

void dotXSI::OffsetBoundingBox ( CSIBCMatrix4x4& in_offMatrix )
{
	for (int b=0;b<m_BoundingBoxList.GetUsed();b++)
	{
		m_BoundingBoxList[b]->SetOffset( in_offMatrix );
	}
}

void dotXSI::OffsetBoundingBox ( CSIBCVector3D& in_offVector )
{
	CSIBCMatrix4x4	l_offsetMatrix;

	l_offsetMatrix.SetTranslation ( in_offVector );

	OffsetBoundingBox ( l_offsetMatrix );
}

void dotXSI::CreateEnvelopes ()
{

	DEBUGENTRY ( "dotXSI::CreateEnvelopes" );

	CSLEnvelopeList* l_pList = m_Scene.EnvelopeList();

	if ( !l_pList )
	{
		return;
	}

	if ( !l_pList->GetEnvelopeCount() )
	{
		return ;
	}
	
	m_pEnvelope = l_pList->Envelopes()[0]->GetEnvelope();

	for (int c=0;c<l_pList->GetEnvelopeCount();c++)
	{
		AddEnvelope ( l_pList->Envelopes()[c] );
	}

	g_aFirstBone.DisposeData ();
}


void dotXSI::AddEnvelope ( CSLEnvelope* in_pEnv )
{
	DEBUGENTRY ( "dotXSI::AddEnvelope" );

	CBone *l_pNewBone = new CBone;

	l_pNewBone->m_pBoneNode = in_pEnv->GetDeformer ();
	
	//
	// We are going to need to inverse of the basepose matrix for each bone
	//

	CSLTransform* l_pBasePose = l_pNewBone->m_pBoneNode->GetBasePose ();

	if (l_pBasePose != NULL)
	{
		l_pBasePose->GetMatrix().GetInverse ( l_pNewBone->m_InvertedBasePose );
	}
	
	m_EnvelopeList.Extend(1);
	m_EnvelopeList[m_EnvelopeList.GetUsed()-1] = l_pNewBone;

	//
	// Assign weights to this bone
	//
		
	//Gets the number of vertices which are modified this bone
	SI_Int numIndicies = in_pEnv->GetVertexWeightCount ();
	SI_Int		*aiIndices;
	SI_Float	*afWeights;

	if ( in_pEnv->GetEnvelope()->Primitive()->Type() == CSLTemplate::SI_MESH )
	{

		CSLMesh*	l_pMesh = (CSLMesh*)in_pEnv->GetEnvelope()->Primitive();
		
		

		if ( m_EnvelopeList.GetUsed() == 1 )
		{
			m_pSourceVertex = l_pMesh->Shape()->GetVertexListPtr ();
			m_pDestVertex = new CSIBCVector3D [ l_pMesh->Shape()->GetVertexCount() ];
			m_iNumVertex = l_pMesh->Shape()->GetVertexCount();

			//
			// Copy the source vertices to the destination buffer in case all weights are at 0
			//

			for (int vc=0;vc<l_pMesh->Shape()->GetVertexCount();vc++)
			{
				m_pDestVertex[vc] = m_pSourceVertex[vc];
			}

			g_aFirstBone.Resize(0);
			g_aFirstBone.Resize( l_pMesh->Shape()->GetVertexCount() );
			memset( g_aFirstBone.ArrayPtr(), false, g_aFirstBone.GetSize() * sizeof( g_aFirstBone[0] ) );
		}

		if ( numIndicies > 0)
		{
		
			aiIndices = new SI_Int[numIndicies];
			afWeights = new SI_Float[numIndicies];
			
			SLVertexWeight*	l_pWeights = in_pEnv->GetVertexWeightListPtr ();
			SI_Int i = 0;
			SI_Int j = 0;
			SI_Int n100Percent = 0;
			SI_Int nFirstBone = 0;
			SI_Int iMaxIndex = 0;
			SI_Int	nWeighted = 0;

			for ( i = 0, iMaxIndex = 0; i < numIndicies; i++ )
			{
				//Get index
				aiIndices[i] = (SI_Int)l_pWeights[i].m_fVertexIndex;	// should this already be an SI_Int?

				//Get float
				afWeights[i] = l_pWeights[i].m_fWeight;
				afWeights[i] /= 100.0f; //scale for 0 to 100 % weights
				
				if ( aiIndices[i] > iMaxIndex ) iMaxIndex = aiIndices[i];
			}
			
			j = g_aFirstBone.GetUsed();
			if ( iMaxIndex >= j )
			{
				g_aFirstBone.Resize( iMaxIndex );
				
				memset( &(g_aFirstBone[j]), 0, ( iMaxIndex - j ) * sizeof( g_aFirstBone[0] ) );
			}
			
			for ( i = 0, n100Percent = 0, nFirstBone = 0; i < numIndicies; i++)
			{
				if ( afWeights[i] >= WEIGHT_EPS_HIGH ) 
				{
					n100Percent++;
				}
				else if ( afWeights[i] > WEIGHT_EPS_LOW )
				{
					
					
					if ( g_aFirstBone[aiIndices[i]] )
					{
						nWeighted++;
					}
					else
					{
						nFirstBone++;
					}
				}
			}
			
			l_pNewBone->m_Weights.Reserve( nWeighted );
			l_pNewBone->m_WeightedIndices.Reserve( nWeighted );
			
			l_pNewBone->m_FirstWeights.Reserve( nFirstBone );
			l_pNewBone->m_FirstWeightedIndices.Reserve( nFirstBone );
			l_pNewBone->m_Indices.Reserve( n100Percent );
				
			for ( i = 0, n100Percent = 0, nWeighted = 0, nFirstBone = 0; i < numIndicies; i++)
			{
				if ( afWeights[i] >= WEIGHT_EPS_HIGH )
				{
					g_aFirstBone[aiIndices[i]]++;
					l_pNewBone->m_Indices[n100Percent] = aiIndices[i];
					++n100Percent;
				}
				else if ( afWeights[i] > WEIGHT_EPS_LOW )
				{
					if ( g_aFirstBone[aiIndices[i]] )
					{
						l_pNewBone->m_WeightedIndices[nWeighted] = aiIndices[i];
						l_pNewBone->m_Weights[nWeighted] = afWeights[i];
						nWeighted ++;
					}
					else
					{
						l_pNewBone->m_FirstWeightedIndices[nFirstBone] = aiIndices[i];
						l_pNewBone->m_FirstWeights[nFirstBone] = afWeights[i];
						nFirstBone ++;
					}
					
					g_aFirstBone[aiIndices[i]]++;
				}
			}
			
			delete [] aiIndices;
			delete [] afWeights;

		}
	}
}
void dotXSI::FlattenGeometry ( CSLModel* in_pModel, RenderNode* in_pNode )
{
	CSLMesh*	l_pMesh = (CSLMesh*)in_pModel->Primitive();
	CSLBaseShape* l_pShape = l_pMesh->Shape();

	CSIBCVector3D* l_PositionList = l_pShape->GetVertexListPtr();
	CSIBCVector3D* l_NormalList = l_pShape->GetNormalListPtr();
	CSIBCColorf* l_ColorList = l_pShape->GetColorListPtr();
	CSIBCVector2D*	l_pUV[4];

	in_pNode->m_bUseColor = l_ColorList != NULL ? true : false;
    
	l_pUV[0] = NULL;
	int	numUVStages = 0;

	CSIBCArray<SuperVertex> l_VertexArray;

	if ( l_pShape->Type() == CSLTemplate::SI_SHAPE )
	{
		CSLShape*	l_p30Shape = (CSLShape*)l_pShape;

		l_pUV[0] = l_p30Shape->GetUVCoordListPtr();
		l_pUV[1] = l_pUV[2] = l_pUV[3] = l_pUV[4] = l_pUV[0];

		numUVStages = 1;

	} else {

		if ( l_pShape->Type() == CSLTemplate::SI_SHAPE35 )
		{
			CSLShape_35*	l_p35Shape = (CSLShape_35*)l_pShape;

			for (int uvCount=0;uvCount<l_p35Shape->GetUVCoordArrayCount();uvCount++)
			{
				CSLUVCoordArray* l_pUVArray = l_p35Shape->UVCoordArrays()[uvCount];

				if ( l_pUVArray != NULL )
				{
					l_pUV[uvCount] = l_pUVArray->GetUVCoordListPtr();
					numUVStages++;

					if ( uvCount == 0 )
					{
						l_pUV[1] = l_pUV[2] = l_pUV[3] = l_pUV[0];
					}
				}

			}

		}
	}

	in_pNode->m_iNbUvs = numUVStages;

	for (int t=0;t<l_pMesh->GetTriangleListCount();t++)
		{
			CSLTriangleList*	l_pTri = l_pMesh->TriangleLists()[t];

			SI_Int*	l_pPos = l_pTri->GetVertexIndicesPtr();
			SI_Int*	l_pNormal = l_pTri->GetNormalIndicesPtr();
			SI_Int*	l_pColor = l_pTri->GetColorIndicesPtr();
			SI_Int* l_pUVindices[5];

			int uvCount;
			for (uvCount = 0;uvCount<l_pTri->GetUVArrayCount();uvCount++)
			{
				l_pUVindices[uvCount] = l_pTri->GetUVIndicesPtr(uvCount);

				if ( uvCount == 0 )
				{
					l_pUVindices[1] = l_pUVindices[2] = l_pUVindices[3] = l_pUVindices[4] = l_pUVindices[0];
				}

			}

			for (int i=0;i<l_pTri->GetTriangleCount();i++)
				{

					for (int v=0;v<3;v++)
					{
						l_VertexArray.Extend(1);
						SuperVertex *Vertex = &l_VertexArray[l_VertexArray.GetUsed()-1];

						int uvCount;

						for (uvCount=0;uvCount<numUVStages;uvCount++)
						{
							CSIBCVector2D*	l_uvarray = l_pUV[uvCount];
							SI_Int*			l_uvindices = l_pUVindices[uvCount];

							Vertex->uv [uvCount][0] = l_uvarray[l_uvindices[(i*3)+v]].GetX();
							Vertex->uv [uvCount][1] = l_uvarray[l_uvindices[(i*3)+v]].GetY();
						}

						if ( l_ColorList )
						{
							Vertex->r = l_ColorList[l_pColor[(i*3)+v]].m_fR;
							Vertex->g = l_ColorList[l_pColor[(i*3)+v]].m_fG;
							Vertex->b = l_ColorList[l_pColor[(i*3)+v]].m_fB;
							Vertex->a = l_ColorList[l_pColor[(i*3)+v]].m_fA;
						}

						Vertex->nx = l_NormalList[l_pNormal[(i*3)+v]].GetX();
						Vertex->ny = l_NormalList[l_pNormal[(i*3)+v]].GetY();
						Vertex->nz = l_NormalList[l_pNormal[(i*3)+v]].GetZ();

						Vertex->x = l_PositionList[l_pPos[(i*3)+v]].GetX();
						Vertex->y = l_PositionList[l_pPos[(i*3)+v]].GetY();
						Vertex->z = l_PositionList[l_pPos[(i*3)+v]].GetZ();
						Vertex->index = l_pPos[(i*3)+v];
					}

					
				}
				
		}

		in_pNode->m_lNBVertex = l_VertexArray.GetUsed ();
		in_pNode->m_pGeometry = new SuperVertex [ in_pNode->m_lNBVertex ];
		memcpy ( in_pNode->m_pGeometry, l_VertexArray.ArrayPtr(), sizeof(SuperVertex) *  in_pNode->m_lNBVertex );

		m_bUseVertexArray = true;

}

void dotXSI::SetCurrentAction ( int in_iActionIdx, LONG in_lPlayFlags)
{ 
	if ( in_lPlayFlags & PLAYBACK_COMPLETE )
	{
		// save current action as pending
		m_iPendingAction = m_iCurrentAction;
	}

	if ( m_lPlaybackFlags & PLAYBACK_COMPLETE )
	{
		m_iPendingAction = in_iActionIdx;
		return;
	}

	m_iCurrentAction = in_iActionIdx; 
	m_lPlaybackFlags = in_lPlayFlags;
	m_iPendingAction = -1;

	if ( in_lPlayFlags & PLAYBACK_RESET )
	{
		m_fTime = 0.0f;
	}


}

void dotXSI::TickEnvelope ()
{
	DEBUGENTRY ( "dotXSI::TickEnvelope" );

	SI_Error					result = SI_SUCCESS;

	CSIBCMatrix4x4	m_InvertedCurrent;
	m_pEnvelope->Transform()->GetGlobalMatrix().GetInverse ( m_InvertedCurrent );

	SI_Int nBones = m_EnvelopeList.GetUsed();

	CSIBCVector3D	*pDest	 = m_pDestVertex;
	CSIBCVector3D	*pSource = m_pSourceVertex;
	CSIBCVector3D	temp;
	
	SI_Int			nVertices;
	SI_Int			*pIndices;
	SI_Float		*pWeights;
	SI_Int			j;
	

	CSIBCMatrix4x4	*pMatrix;

	for ( SI_Int i = 0; i < nBones; i++)
	{
		CBone		*pBone = m_EnvelopeList[i];

		
		pBone->m_pBoneNode->Transform()->ComputeLocalMatrix();
		pBone->m_pBoneNode->Transform()->ComputeGlobalMatrix();
		m_InvertedCurrent.Multiply( pBone->m_pBoneNode->Transform()->GetGlobalMatrix(), 
			pBone->m_Current );
		
		pBone->m_Current.Multiply( pBone->m_InvertedBasePose );

		if (m_pEnvelope->GetBasePose () != NULL)
		{
			CSIBCMatrix4x4	l_m4Temp(m_pEnvelope->GetBasePose ()->GetMatrix ());
			pBone->m_Current.Multiply( l_m4Temp );
		}
		
		nVertices = pBone->m_FirstWeightedIndices.GetUsed();
		pIndices = pBone->m_FirstWeightedIndices.ArrayPtr();
		pWeights = pBone->m_FirstWeights.ArrayPtr();
		
		pMatrix = &pBone->m_Current;
		
		for ( j = 0; j < nVertices; ++j, ++pIndices, ++pWeights )
		{
			pMatrix->Multiply( temp, pSource[*pIndices] );
			temp.Scale( pDest[*pIndices], *pWeights );
		}
		
		nVertices = pBone->m_WeightedIndices.GetUsed();
		pIndices = pBone->m_WeightedIndices.ArrayPtr();
		pWeights = pBone->m_Weights.ArrayPtr();
		
		for ( j = 0; j < nVertices; ++j, ++pIndices, ++pWeights )
		{
			pMatrix->Multiply( temp, pSource[*pIndices] );
			temp.ScaleAndAdd( pDest[*pIndices], *pWeights );
		}
		
		nVertices = pBone->m_Indices.GetUsed();
		pIndices = pBone->m_Indices.ArrayPtr();
		
		for ( j = 0; j < nVertices; ++j, ++pIndices )
		{
			pMatrix->Multiply( pDest[*pIndices], pSource[*pIndices] );
		}
		
	}

	//
	// transform flatten geometry
	//

	for (int n=0;n<m_pRenderNodes.GetUsed();n++)
	{
		RenderNode* l_pRN = m_pRenderNodes[n];

		for (LONG v=0;v<l_pRN->m_lNBVertex;v++)
		{
			SuperVertex* l_pSV = &l_pRN->m_pGeometry[v];
			CSIBCVector3D* l_pDestVert = &m_pDestVertex[l_pSV->index];

			l_pSV->x = l_pDestVert->m_fX;
			l_pSV->y = l_pDestVert->m_fY;
			l_pSV->z = l_pDestVert->m_fZ;


		}
	}

#ifdef ANALBOUNDINGBOX
	for (int b=0;b<GetBoundingBoxList().GetUsed();b++)
	{
		BoundingBox* l_pBB = GetBoundingBoxList()[b];
		l_pBB->Reset();

		for (int v=0;v<m_iNumVertex;v++)
		{
			l_pBB->Grow ( pDest[v] );
		}



	}
#endif


}
