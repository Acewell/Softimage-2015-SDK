//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCMatrix.h
	\brief Defines the CSIBCMatrix4x4 class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCMatrix_H__
#define __CSIBCMatrix_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCVector.h>

#ifdef _PSX2
#include <libvu0.h>
#endif

//***************************************************************************************
// Typedefs
//***************************************************************************************

//***************************************************************************************
// CSIBCMatrix4x4 | Matrices are stored in column major order, e.g., m_Matrix[ROW][COLUMN]
//***************************************************************************************

/*! \brief Class representing matricies with 4 rows, and 4 columns.

	CSIBCMatrix4x4 objects store values in column-major order (the form which C/C++ stores them).
	In fact, the data values for the matrix stored within the object are represented with a
	SI_Matrix, which is a typedef for a 4x4 C matrix (this is true \e except on the Playstation 2).
	Special optimizations for this class are made on the Playstation 2 to use the VU processor.

	This class uses double precision floating point numbers to store element values. There exists
	three other matrix classes, CSIBCMatrix44d, CSIBCMatrix33d and CSIBCMatrixMNd. They are used
	to represent 4x4 matricies with double precision floating-point numbers, 3x3 matricies with double
	precision floating-point numbers, and MxN matricies with double precision floating-point numbers,
	respectively.
*/
class XSICOREEXPORT CSIBCMatrix4x4
{
	public:

		/*! Default constructor.
			Sets the matrix to the identity matrix.
		*/
		CSIBCMatrix4x4();

		/*! Copy constructor.
			Sets the matrix to be identical to the \p i_Matrix matrix.
			\param[in]	i_Matrix	The matrix to copy values for the new matrix from.
		*/
		CSIBCMatrix4x4( const CSIBCMatrix4x4 & i_Matrix);

		/*! Constructor.
			Sets the matrix values to those contained in the \p i_pMatrix array. The array
			should be in column-major form. That is, [row][column] matches with
			\p i_pMatrix[column*4 + row].
			\param[in]	i_pMatrix	Array of 16 SI_Float values in column-major form to set the new matrix to.
			\sa CSIBCMatrix4x4::Set(const SI_Float *)
		*/
		CSIBCMatrix4x4( SI_Float * i_pMatrix);

		~CSIBCMatrix4x4();												// Default Destructor

		// Components

		/*!	Sets the values in this matrix to the values in the \p i_Matrix matrix.
			\param[in] i_Matrix	The matrix to set this matrix's values to.
			\retval	SI_Error::SI_SUCCESS The matrix was set properly.
		*/
		SI_Error Set( const CSIBCMatrix4x4 & i_Matrix);

		/*! Sets the matrix values to those contained in the \p i_pMatrix array. The array
			should be in column-major form. That is, [row][column] matches with
			\p i_pMatrix[column*4 + row].
			\param[in]	i_pMatrix	Array of 16 SI_Float values in column-major form to set the matrix to.
			\retval	SI_Error::SI_SUCCESS The matrix was set properly.

			\eg Example of setting a matrix
			\code
			SIBCMatrix4x4 *	t_mMyMatrix = new SIBCMatrix();	// set to identity

			// Assume that OpenGL is up and running, and get the GL_MODELVIEW matrix.
			GLfloat		t_fModelView[16];
			glGetFloatv(GL_MODELVIEW_MATRIX, t_fModelView);

			// It is stored in column-major form, so we can now set our matrix to the GL_MODELVIEW matrix.
			t_mMyMatrix->Set((SI_Float *)t_fModelView);

			// Same with Direct3D. Assume we have it up and running, and now set our matrix
			// to the D3DTS_VIEW matrix (v8.1).
			D3DXMATRIX	t_mView;
			m_pDevice->GetTransform(D3DTS_VIEW, &t_mView);
			t_mMyMatrix->Set((SI_Float *)t_mView);
			\endcode

			\sa CSIBCMatrix4x4::CSIBCMatrix4x4(const SI_Float *)
		*/
		SI_Error Set( const SI_Float * i_pMatrix);

		/*!	Sets the value at \p i_bIndex to i_fValue. The index is a column-major index of the item to set.
			\param[in]	i_bIndex	The column-major index of the item to set.
			\param[in]	i_fValue	The value to set the element to.
			\retval	SI_Error::SI_SUCCESS The matrix was set properly.
			\sa CSIBCMatrix4x4::Set(const SI_Byte, const SI_Byte, SI_Float)
			\sa CSIBCMatrix4x4::Get(const SI_Byte)
		*/
		SI_Error Set( const SI_Byte i_bIndex, SI_Float i_fValue);

		/*!	Sets the value at row \p i_Row and column \p i_Column to i_fValue.
			\param[in]	i_Column	The column of the item to set.
			\param[in]	i_Row		The row of the item to set.
			\param[in]	i_fValue	The value to set the element to.
			\retval	SI_Error::SI_SUCCESS The matrix was set properly.
			\sa CSIBCMatrix4x4::Set(const SI_Byte, SI_Float)
			\sa CSIBCMatrix4x4::Get(const SI_Byte, const SI_Byte)
		*/
		SI_Error Set(	const SI_Byte i_Column,
						const SI_Byte i_Row,
						const SI_Float i_fValue);

		/*! Sets this matrix to a scaling matrix, whose X, Y and Z values are obtained from the
			X, Y and Z components of the \p i_vScale vector. This function replaces the current
			matrix.
			\param[in]	i_vScale	The vector containing the X, Y and Z scaling factors for the matrix.

			\sa CSIBCMatrix4x4::GetScaling
			\sa CSIBCMatrix4x4::SetScaling
			\sa CSIBCMatrix4x4::SetTransforms
		*/
		void SetToScale( const CSIBCVector3D & i_vScale);

		/*! Sets this matrix to a rotation matrix, determined by the euler angles supplied in \p i_vEuler vector.
			The euler angle convention used is the "xyz" convention (better known as the pitch-roll-yaw angles).
			This function replaces the current matrix.
			\param[in]	i_vEuler	The euler angles to compute the values for this matrix. X is 'pitch', Y is 'roll' and Z is 'yaw'.

			\sa CSIBCMatrix4x4::SetRotation
			\sa CSIBCMatrix4x4::GetRotation
			\sa CSIBCMatrix4x4::SetTransforms
		*/
		void SetToRotation( const CSIBCVector3D & i_vEuler);

		/*! Sets this matrix to a rotation matrix, determined by a counter-clockwise rotation of \p angl radians,
			about an axis \p axis. This function replaces the current matrix.
			\param[in]	angl	The angle of counter-clockwise rotation (in radians) about the axis.
			\param[in]	axis	The vector representing the axis in which to rotate about.
		*/
		void SetToRotation( const SI_Float angl, const CSIBCVector3D &axis );

		/*! Sets this matrix to a translation matrix, determined by the vector \p i_vTrans, containing
			the amount of translation in each axis. This function replaces the current matrix.
			\param[in]	i_vTrans	Vector containing translations.
		*/
		void SetToTranslation( const CSIBCVector3D & i_vTrans);

		/*! Sets this matrix with euler rotation, scale, and translation transformations produced from the
			\p rot, \p scale, and \p trans vectors respectively. This function sets the current matrix to
			a rotation matrix with the \p rot parameter (equivalent to what gets produced from
			CSIBCMatrix4x4::SetToRotation), then applies a scaling to the matrix, and then applies the
			transformation. However, it is not the equivalent of matrix multiplication, the translation
			is not scaled. This function replaces the current matrix.

			\param[in]	scale	Vector representing the scaling in the X, Y and Z directions.
			\param[in]	rot		Vector representing the euler rotation angles (pitch, roll, yaw).
			\param[in]	trans	Vector representing the translations in the X, Y and Z directions.

			\sa CSIBCMatrix4x4::SetToRotation
			\sa	CSIBCMatrix4x4::SetToScale
			\sa CSIBCMatrix4x4::SetToTranslation

			\eg Example of using SetTransforms
			\code
			CSIBCMatrix4x4	t_mMatrix1, t_mMatrix2, t_mMatrix3, t_mMatrixProd, t_mMatrixTransforms;
			CSIBCVector3D	t_vScale, t_vRot, t_vTrans;

			t_vScale	= CSIBCVector3D(2.0f, 4.0f, 1.0f);			// scale 2x in X, 4x in Y, and 1x in Z.
			t_vRot		= CSIBCVector3D(M_PI_4, M_PI_4, M_PI_4);	// pitch and roll of 45deg, 180deg heading.
			t_vTrans	= CSIBCVector3D(10.0f, -10.0f, 5.0f);		// translation of 10.0f, -10.0f, 5.0f in X, Y, Z respectively.

			// Do the 'SetTo...' command for each of three transformation types, and multiply the results.
			t_mMatrix1.SetToRotation(t_vRot);
			t_mMatrix2.SetToScale(t_vScale);
			t_mMatrix3.SetToTranslation(t_vTrans);
			t_mMatrixProd = t_mMatrix1 * t_mMatrix2 * t_mMatrix3;

			// Now do the 'all-in-one' on another matrix, using the same inputs.
			t_mMatrixTransforms.SetTransforms(t_vScale, t_vRot, t_vTrans);

			// Notice that these matricies are not equal
			\endcode
		*/
		void SetTransforms( const CSIBCVector3D &scale,
							const CSIBCVector3D &rot,
							const CSIBCVector3D &trans );


		/*! Sets the scaling factor in X, Y and Z directions, using the values from the corresponding components
			in the \p i_vScaling vector. This function first normalizes the scaling of the current matrix, and then
			scales the matrix by the given amount.

			\param[in] i_vScaling	Vector representing the desired scaling in X, Y and Z.

			\sa CSIBCMatrix4x4::SetToScale
			\sa CSIBCMatrix4x4::GetScaling

			\eg Example of using SetScaling
			\code
			CSIBCMatrix4x4		t_mMatrix1, t_mMatrix2;
			CSIBCVector3D		t_vScaling;

			// Create two identical scaling matricies.
			t_vScaling = CSIBCVector3D(5.0f, 10.0f, 0.5f);
			t_mMatrix1.SetToScale(t_vScaling);
			t_mMatrix2.SetToScale(t_vScaling);

			// Now use SetScaling on one, with the same scale vector.
			t_mMatrix1.SetScaling(t_vScaling);

			// Notice that t_mMatrix1 == t_mMatrix2, because SetScaling normalizes scaling.
			\endcode
		*/
		void SetScaling( const CSIBCVector3D & i_vScaling);

		/*! Sets the rotation in the matrix to the euler rotation given by the angles in \p i_vRot (as pitch-roll-yaw).
			The scaling and transformation of the matrix are kept constant. For more efficiency, if a rotation matrix
			has already been computed, use CSIBCMatrix4x4::SetRotation( const CSIBCMatrix4x4 &).

			\param[in] i_vRot	The euler rotation angles to set the rotation of this matrix to (as pitch-roll-yaw angles).

			\sa CSIBCMatrix4x4::SetRotation(const CSIBCMatrix4x4 &)
			\sa CSIBCMatrix4x4::GetRotation
			\sa CSIBCMatrix4x4::GetTransforms
			\sa CSIBCMatrix4x4::SetToRotation

			\eg Example using SetRotation
			\code
			CSIBCMatrix4x4		t_mMatrix;
			CSIBCVector3D		t_vTrans, t_vScale, t_vRot;
			CSIBCVector3D		t_vTrans2, t_vScale2, t_vRot2;

			// Set the components of the matrix.
			t_vTrans = CSIBCVector3D(1.5f, 2.5f, 0.25f);
			t_vScale = CSIBCVector3D(500.0f, 0.01f, 500.0f);
			t_vRot   = CSIBCVector3D(M_PI_4, M_PI_4, M_PI_4);
			t_mMatrix.SetTransforms(t_vScale, t_vRot, t_vTrans);

			// Now set the rotation to a different value..
			t_vRot = CSIBCVector3D(M_PI, M_PI_4, M_PI);
			t_mMatrix.SetRotation(t_vRot);

			// Notice that the scaling and translation components are the same.
			t_mMatrix.GetTransforms(t_vScale2, t_vRot2, t_vTrans2);
			printf("t_vScale == t_vScale2 = %s\n", (t_vScale == t_vScale2) ? "TRUE", "FALSE);
			printf("t_vRot == t_vRot2 = %s\n", (t_vRot == t_vRot2) ? "TRUE", "FALSE);
			printf("t_vTrans == t_vTrans2 = %s\n", (t_vTrans == t_vTrans2) ? "TRUE", "FALSE);
			\endcode
		*/
		void SetRotation( const CSIBCVector3D & i_vRot);

		/*! Sets the rotation in the matrix to the rotation given by the rotation matrixin \p i_mMatrix.
			The scaling and transformation of the matrix are kept constant. This function is more efficient
			than its counterpart, CSIBCMatrix4x4::SetRotation( const CSIBCVector3D &), if a rotation matrix
			has already been computed.

			\param[in]	i_mMatrix	Rotation matrix containing the desired rotation for this matrix.

			\sa CSIBCMatrix4x4::SetRotation( const CSIBCVector3D &)
			\sa CSIBCMatrix4x4::SetToRotation
			\sa CSIBCMatrix4x4::GetRotation
		*/
		void SetRotation( const CSIBCMatrix4x4 & i_mMatrix);

		/*! Sets the rotation in the matrix to the rotation defined by the three axes given by the parameters
			\p x_axis, \p y_axis and \p z_axis. The scaling and translation of the matrix are kept constant.
			This function is similar in functionality to CSIBCMatrix4x4::SetRotation, with different parameters,
			and is more efficient than CSIBCMatrix4x4::SetRotation( const CSIBCVector3D &).

			\param[in]	x_axis	Normalized vector to use as the x-axis of the desired rotation.
			\param[in]	y_axis	Normalized vector to use as the y-axis of the desired rotation.
			\param[in]	z_axis	Normalized vector to use as the z-axis of the desired rotation.

			\sa CSIBCMatrix4x4::GetOrientation
			\sa CSIBCMatrix4x4::GetRotation
			\sa	CSIBCMatrix4x4::SetRotation
			\sa	CSIBCMatrix4x4::SetToRotation
		*/
		void SetOrientation(	const CSIBCVector3D &x_axis,
								const CSIBCVector3D &y_axis,
								const CSIBCVector3D &z_axis );

		/*! Set the translation in the matrix to the translation in the X, Y and Z directions given by the
			components of the vector \p i_vTrans. The scaling and rotation of the matrix is kept constant.

			\param[in]	i_vTrans	The vector representing the desired translation in the X, Y and Z directions.

			\sa CSIBCMatrix4x4::GetTranslation
			\sa CSIBCMatrix4x4::SetToTranslation
		*/
		void SetTranslation( const CSIBCVector3D & i_vTrans);

		// Retrieve Information.

		/*! Returns the entire matrix into an array of 16 SI_Float values (in column-major order).
			\param[out]	o_pMatrix	Allocated array of 16 SI_Float, to receive the matrix values.
			\retval SI_Error::SI_SUCCESS The matrix was obtained successfully.
			\sa CSIBCMatrix4x4::Raw
		*/
		SI_Error Get( SI_Float * o_pMatrix) const;

		/*! Returns the entire matrix into another CSIBCMatrix4x4 object. The values inside \c o_mMatrix
			are overwritten with the values from this matrix.
			\param[out]	o_mMatrix	Matrix to receive the values from this matrix.
			\retval SI_Error::SI_SUCCESS The matrix was obtained successfully.
			\sa CSIBCMatrix4x4::operator=
		*/
		SI_Error Get( CSIBCMatrix4x4 & o_mMatrix) const;

		/*! Returns the value at the specified index. The index is a column-major index of the item to get.
			\param[in]	i_bIndex	The column-major index of the item to get.
			\return	The value of the item at the given index.
			\sa CSIBCMatrix4x4::Set(const SI_Byte, SI_Float)
		*/
		SI_Float Get( const SI_Byte i_bIndex) const;


		/*!	Returns the value at the specified row-column juncture.
			\param[in]	i_Column	The column of the item to get.
			\param[in]	i_Row		The row of the item to get.
			\return	The value of the item at the given index.
			\sa CSIBCMatrix4x4::Set(const SI_Byte, const SI_Byte, const SI_Float)
		*/
		SI_Float Get( const SI_Byte i_Column, const SI_Byte i_Row) const;	// Retrieves the value at an index 2d

		/*! Returns the scaling components for this matrix in the X, Y and Z directions.
			\param[out]	o_vScale	Vector to receive the scaling components for this matrix.
			\sa	CSIBCMatrix4x4::SetScaling
		*/
		void GetScaling( CSIBCVector3D & o_vScale) const;

		/*! Returns the euler rotation angles for this matrix (as pitch-roll-yaw angles).
			\param[out]	o_vRot		Vector to receive the euler rotation angles for this matrix.
			\sa CSIBCMatrix4x4::SetRotation( const CSIBCVector3D & )
		*/
		void GetRotation( CSIBCVector3D & o_vRot) const ;						// Gets the rotation values for euler xyz

		/*! Returns the orientation axes for the rotation of this matrix.
			\param[in]	x_axis	Receives the x-axis of the rotation for this matrix.
			\param[in]	y_axis	Receives the y-axis of the rotation for this matrix.
			\param[in]	z_axis	Receives the z-axis of the rotation for this matrix.
			\sa CSIBCMatrix4x4::SetOrientation
			\sa CSIBCMatrix4x4::GetRotation
		*/
		void GetOrientation(	CSIBCVector3D &x_axis,
								CSIBCVector3D &y_axis,
								CSIBCVector3D &z_axis ) const ;

		/*! Returns the translation for this matrix.
			\param[out]	o_vTrans	Receives the translation in the X, Y and Z directions for this matrix.
			\sa CSIBCMatrix4x4::SetTranslation
			\sa CSIBCMatrix4x4::SetToTranslation
		*/
		void GetTranslation( CSIBCVector3D & o_vTrans) const;

		/*! Returns the scaling, rotation, and translation of the current matrix. This is equivalent to calling
			CSIBCMatrix4x4::GetScaling, CSIBCMatrix4x4::GetRotation and CSIBCMatrix4x4::GetTranslation, with the
			corresponding inputs.
			\param[out]	scale	Receives the scaling of this matrix in the X, Y and Z directions.
			\param[out]	rot		Receives the euler angle rotations of this matrix (in pitch-roll-yaw angles).
			\param[out]	trans	Receives the translation of this matrix in the X, Y and Z directions.

			\sa CSIBCMatrix4x4::SetTransforms
			\sa CSIBCMatrix4x4::GetScaling
			\sa CSIBCMatrix4x4::GetRotation
			\sa CSIBCMatrix4x4::GetTranslation
		*/
		void GetTransforms( CSIBCVector3D &scale,
							CSIBCVector3D &rot,
							CSIBCVector3D &trans );

		/*! Determines whether this matrix is the identity matrix.
			\retval SI_Bool::TRUE if the matrix is the identity matrix
			\retval SI_Bool::FALSE otherwise.
		*/
        SI_Bool IsIdentity();

		// Operations

		/*!	Computes the inverse of this matrix, and stores it in \c o_mMatrix. The contents
			of \c o_mMatrix are overwritten in this process.

			\param[out]	o_mMatrix	Receives the inverse of this matrix.
			\retval	SI_Bool::TRUE if the inverse can be computed (\c o_mMatrix contains the inverse),
			\retval	SI_Bool::FALSE otherwise (the contents of \c o_mMatrix are unchanged).
		*/
        SI_Bool GetInverse( CSIBCMatrix4x4 & o_mMatrix);

		/*! Not implemented. */
		CSIBCMatrix4x4& Normalize();

		/*! Sets each value in the matrix to zero.
			\return	Reference to this matrix.
			\sa CSIBCMatrix4x4::SetIdentity
		*/
		CSIBCMatrix4x4& SetNull();

		/*! Sets the matrix to the identity matrix.
			\return	Reference to this matrix.
			\sa CSIBCMatrix4x4::IsIdentity
			\sa CSIBCMatrix4x4::SetNull
		*/
		CSIBCMatrix4x4& SetIdentity();

		/*! Sets this matrix to be its transpose matrix.
			\return Reference to this matrix.
		*/
		CSIBCMatrix4x4& Transpose();

		/*! Copies the contents of this matrix into the 16 SI_Float array \p o_pMatrix in
			column major order. This method is equivalent in functionality to
			SIBCMatrix4x4::Get(SI_Float *).
			\param[out]	o_pMatrix	Array of 16 SI_Float values to receive the contents of this matrix.
			\sa CSIBCMatrix4x4::Get(SI_Float *)
			\sa CSIBCMatrix4x4::Raw
			\sa CSIBCMatrix4x4::RowMajor
		*/
		void ColumnMajor( SI_Float * o_pMatrix);

		/*! Copies the contents of this matrix into the 16 SI_Float output array in row major order.
			\sa CSIBCMatrix4x4::ColumnMajor
		*/
		void RowMajor( SI_Float * /*!< Array of 16 SI_Float values to receive the contents of this matrix. */);		// Copies the matrix in row major format

		/*! Returns a pointer to the raw data of the matrix (16 SI_Float values in column major order).
			The pointer received from this function should not be freed, and modification to the values in
			the array directly modify this matrix object.
			\return	Array of 16 SI_Float values containing the contents of this matrix.

			\sa CSIBCMatrix4x4::GetSIMatrix
			\sa CSIBCMatrix4x4::ColumnMajor
			\sa CSIBCMatrix4x4::Get(SI_Float *)
		*/
		SI_Float *Raw();

		/*!	Returns a pointer to the SI_Matrix containing the data used internally by this matrix object.
			The pointer received from this function should not be freed, and modification to the values within
			directly modify this matrix object.
			\return	Pointer to the SI_Matrix containing the values for this matrix object.
		*/
		SI_Matrix *GetSIMatrix() { return &m_Matrix; }

		/*! Computes the \a camera positioning matrix, such that the camera is located at position \p pos,
			it pointing at \p target. The up vector of the camera is given by \p up, and the camera is
			rotated about the position-target vector an angle of \p roll counter-clockwise from the up vector.
			This call replaces the current matrix.

			\param[in]	pos		The desired position of the camera, in world coordinates.
			\param[in]	target	The desired interest point of the camera, in world coordinates.
			\param[in]	up		The up vector of the camera.
			\param[in]	roll	The counter-clockwise roll angle (in degrees) from the up vector about the position-target vector.
		*/
		void LookAt( const CSIBCVector3D &pos,
					 const CSIBCVector3D &target,
					 const CSIBCVector3D &up,
					 const SI_Float roll );


		/*! Computes an orthogonal projection matrix. This call replaces the current matrix.

			\param[in]	left		The left boundary of the viewing plane.
			\param[in]	right		The right boundary of the viewing plane.
			\param[in]	top			The top boundary of the viewing plane.
			\param[in]	bottom		The bottom boundary of the viewing plane.
			\param[in]	nearPlane	The distance of the near clipping plane from the viewing position.
			\param[in]	farPlane	The distance of the far clipping plane from the viewing position.

			\sa	CSIBCMatrix4x4::Perspective
			\sa	CSIBCMatrix4x4::PerspectiveAlt
		*/

		void Ortho( const SI_Float left,
					const SI_Float right,
					const SI_Float top,
					const SI_Float bottom,
					const SI_Float nearPlane,
					const SI_Float farPlane);

		/*! Computes a perspective projection matrix. This call produces a perspective projection
			matrix compatible with OpenGL projection matricies. To produce a matrix that it compatible
			with Direct3D, use CSIBCMatrix4x4::PerspectiveAlt. This call replaces the current matrix.

			\param[in]	nearPlane	The distance of the near clipping plane from the viewing position.
			\param[in]	farPlane	The distance of the far clipping plane from the viewing position.
			\param[in]	fov			The half field-of-view angle in radians. The actual view angle is double this value.
			\param[in]	aspect		The aspect ratio (width/height) for the perspective matrix.

			\sa	CSIBCMatrix4x4::PerspectiveAlt
			\sa	CSIBCMatrix4x4::Ortho
		*/
		void Perspective(	const SI_Float nearPlane,
							const SI_Float farPlane,
							const SI_Float fov,
							const SI_Float aspect );

		/*! Computes a perspective projection matrix. This call produces a perspective projection
			matrix compatible with Direct3D projection matricies. To produce a matrix that it compatible
			with OpenGL, use CSIBCMatrix4x4::Perspective. This call replaces the current matrix.

			\param[in]	nearPlane	The distance of the near clipping plane from the viewing position.
			\param[in]	farPlane	The distance of the far clipping plane from the viewing position.
			\param[in]	fov			The half field-of-view angle in radians. The actual view angle is double this value.
			\param[in]	aspect		The aspect ratio (width/height) for the perspective matrix.

			\sa	CSIBCMatrix4x4::Perspective
			\sa	CSIBCMatrix4x4::Ortho
		*/
		void PerspectiveAlt(	const SI_Float nearPlane,
								const SI_Float farPlane,
								const SI_Float fov,
								const SI_Float aspect );

		/*! Computes a rotation matrix where the x-axis is given by the vector \p x_vec, the y-axis
			lies in the plane defined by the \p x_vec and \p xy_vec vectors, and the z-axis is the
			cross-product between \p x_vec and \p xy_vec. This call replaces the current matrix.

			\param[in]	x_vec	Pointer to the vector to use as the x-axis of the rotation matrix.
			\param[in]	xy_vec	Pointer to the vector to define the plane (along with \p x_vec) in which the y-axis lies.
			\retval	SI_Bool::TRUE if the rotation matrix was computed properly, this matrix contains the new
					rotation matrix.
			\retval	SI_Bool::FALSE otherwise, this matrix contains the identity matrix.

			\sa CSIBCMatrix4x4::AlignRoll
		*/
		SI_Bool AlignAxes(	CSIBCVector3D *x_vec,
							CSIBCVector3D *xy_vec );

		/*! Computes a rotation matrix which is pointing along the vector \p in_pVector, with a roll angle
			of \p in_Roll. This call replaces the current matrix.

			\param[in]	in_Roll		The roll angle (in radians) for the rotation matrix.
			\param[in]	in_pVector	Pointer to the vector defining the desired rotation of the new matrix.
			\retval	 SI_Bool::TRUE
			\sa CSIBCMatrix4x4::AlignAxes
		*/
		SI_Bool AlignRoll(	SI_Float		in_Roll,
							CSIBCVector3D	*in_pVector);

		/*! Replaces this matrix with the matrix-product between this matrix and \p i_mMatrix.
			This matrix is right-multiplied by the input matrix, thus the operation is as follows:
			<TT>Mthis' = Mthis * Minput</TT>.

			\param[in]	i_mMatrix	The matrix to multiply this matrix by.
			\return	Reference to this matrix.
			\sa	CSIBCMatrix4x4::Multiply(CSIBCMatrix4x4&, CSIBCMatrix4x4&)
			\sa	CSIBCMatrix4x4::operator*(CSIBCMatrix4x4&)
		*/
		CSIBCMatrix4x4 &Multiply( CSIBCMatrix4x4 & i_mMatrix);

		/*! Computes the matrix-product between this matrix and \p i_mMatrix. This matrix is
			right-multiplied by the input matrix, thus the operation is as follows:
			<TT>Mout = Mthis * Minput</TT>.

			\param[in]	i_mMatrix	The matrix to multiply this matrix by.
			\param[out]	result		Reference to the matrix to store the multiplication results.
			\retval SI_Error::SI_SUCCESS The matrix was multiplied successfully.
			\sa	CSIBCMatrix4x4::Multiply(CSIBCMatrix4x4&)
			\sa	CSIBCMatrix4x4::operator*(CSIBCMatrix4x4&)
		*/
		SI_Error Multiply(	CSIBCMatrix4x4 & i_mMatrix,
							CSIBCMatrix4x4 &result);

		/*! Replaces this matrix with the matrix-product between this matrix and \p i_mMatrix. The last
			column of the matrix is not computed, and is set to <TT>(0,0,0,1)</TT>. This matrix is
			right-multiplied by the input matrix, thus the operation is as follows:
			<TT>Mthis' = Mthis * Minput</TT>.

			\param[in]	i_mMatrix	The matrix to multiply this matrix by.
			\return	Reference to this matrix.
			\sa CSIBCMatrix4x4::Multiply4x3(const CSIBCMatrix4x4&, CSIBCMatrix4x4&)
			\sa	CSIBCMatrix4x4::Multiply(CSIBCMatrix4x4 &)
		*/
		CSIBCMatrix4x4 &Multiply4x3( const CSIBCMatrix4x4 & i_mMatrix);

		/*! Computes the matrix-product between this matrix and \p i_mMatrix. The last column of the
			matrix is not computed, and is set to <TT>(0,0,0,1)</TT>. This matrix is right-multiplied by the
			input matrix, thus the operation is as follows: <TT>Mout = Mthis * Minput</TT>.

			\param[in]	i_mMatrix	The matrix to multiply this matrix by.
			\param[out]	result		Reference to the matrix to store the multiplication results.
			\retval SI_Error::SI_SUCCESS The matrix was multiplied successfully.
			\sa CSIBCMatrix4x4::Multiply4x3(const CSIBCMatrix4x4&)
			\sa	CSIBCMatrix4x4::Multiply(CSIBCMatrix4x4 &)
		*/
		SI_Error Multiply4x3(	const CSIBCMatrix4x4 & i_mMatrix,
								CSIBCMatrix4x4 &result) const;

		/*! Computes the matrix-product between this matrix and the row vector \p i_vVector. The Z and
			W values of the vector (to make the multiplication possible) are assumed to be \c 0.0f and
			\c 1.0f, respectively. The vector is right-multiplied by this matrix, thus the operation is
			as follows: <TT>Vout = Vin * Mthis</TT>.

			\param[in]	i_vVector		Row vector to multiply with this matrix.
			\return	Resulting vector from the multiplication.

			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector4D&)
			\sa CSIBCMatrix4x4::operator*(CSIBCVector2D &)
		*/
		CSIBCVector4D Multiply( const CSIBCVector2D & i_vVector) const;

		/*! Computes the matrix-product between this matrix and the row vector \p i_vVector. The \c W value
			of the vector (to make the multiplication possible) is assumed to be \c 1.0f. The vector is
			right-multiplied by this matrix thus the operation is as follows: <TT>Vout = Vin * Mthis</TT>.

			\param[in]	i_vVector		Row vector to multiply with this matrix.
			\return	Resulting vector from the multiplication.

			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector2D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector4D&)
			\sa	CSIBCMatrix4x4::Multiply(CSIBCVector3D&, const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::MultiplyLeft
			\sa CSIBCMatrix4x4::operator*(CSIBCVector3D&)
		*/
		CSIBCVector4D Multiply( const CSIBCVector3D & i_vVector);

		/*! Computes the matrix-product between this matrix and the row vector \p i_vVector. The vector is
			right-multiplied by this matrix thus the operation is as follows: <TT>Vout = Vin * Mthis</TT>.

			\param[in]	i_vVector		Row vector to multiply with this matrix.
			\return	Resulting vector from the multiplication.

			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector2D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector3D&)
			\sa CSIBCMatrix4x4::operator*(CSIBCVector4D&)
		*/
		CSIBCVector4D Multiply( const CSIBCVector4D & i_vVector);

		/*! Computes the matrix-product between this matrix and the row vector \p i_vVector. The \c W value
			of the vector (to make the multiplication possible) is assumed to be \c 1.0f. The vector is
			right-multiplied by this matrix thus the operation is as follows: <TT>Vout = Vin * Mthis</TT>.

			\note Only the \c X, \c Y and \c Z values of the resultant vector are given in the result \p i_vResult.

			\param[in]	i_vVector	Row vector to multiply with this matrix.
			\param[in]	i_vResult	Resulting vector from the multiplication.

			\sa	CSIBCMatrix4x4::MultiplyLeft
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector2D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector4D&)
		*/
		void Multiply( CSIBCVector3D &i_vResult, const CSIBCVector3D &i_vVector );

		/*! Computes the matrix-product between this matrix and the column vector \p i_vVector. The \c W value
			of the vector (to make the multiplication possible) is assumed to be \c 1.0f. The vector is
			left-multiplied by this matrix thus the operation is as follows: <TT>Vout = Mthis * Vin</TT>.

			\note Only the \c X, \c Y and \c Z values of the resulting vector are given in the result \p i_vResult.

			\param[in]	i_vVector	Row vector to multiply with this matrix.
			\param[in]	i_vResult	Resultant vector from the multiplication.

			\sa	CSIBCMatrix4x4::Multiply(CSIBCVector3D&, const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector2D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector4D&)
		*/
		void MultiplyLeft( CSIBCVector3D & i_vResult, const CSIBCVector3D &i_vVector ) const;

#ifdef _PSX2

		/*! Playstation 2 specific. Caches the current matrix into the Playstation 2 VU processor.
			This call does not do any actual matrix multiplications, but is used along with
			CacheMultiply, CacheMultiplyScale, CacheMultiplyScaleAdd to perform optimized matrix
			multipliations on the Playstation 2.

			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector3D &, CSIBCVector3D &)
			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector4D &, const CSIBCVector4D &)
			\sa CSIBCMatrix4x4::CacheMultiplyScale
			\sa CSIBCMatrix4x4::CacheMultiplyScaleAdd
		*/
		void CacheMatrix();

		/*! Playstation 2 specific. Right-multiplies the input vector \p i_vVector by the last
			cached matrix (See CSIBCMatrix4x4::CacheMatrix). The \c W value of the vector is assumed
			to be \c 1.0f (so that multiplication can occur). The operation is as follows:
			<TT>Vout = Vin * Mcache</TT>.

			\param[in]	i_vResult	Stores the result of the matrix-product.
			\param[in]	i_vVector	The vector to be multiplied.

			\sa	CSIBCMatrix4x4::CacheMatrix
			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector4D &, const CSIBCVector4D &)
			\sa CSIBCMatrix4x4::CacheMultiplyScale
			\sa CSIBCMatrix4x4::CacheMultiplyScaleAdd
		*/
		void CacheMultiply( CSIBCVector3D & i_vResult, CSIBCVector3D & i_vVector);

		/*!	Playstation 2 specific. Right-multiplies the input vector \p i_vVector by the last
			cached matrix (See CSIBCMatrix4x4::CacheMatrix). The operation is as follows:
			<TT>Vout = Vin * Mcache</TT>.

			\param[in]	i_vResult	Stores the result of the matrix-product.
			\param[in]	i_vVector	The vector to be multiplied.

			\sa	CSIBCMatrix4x4::CacheMatrix
			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector3D &, const CSIBCVector3D &)
			\sa CSIBCMatrix4x4::CacheMultiplyScale
			\sa CSIBCMatrix4x4::CacheMultiplyScaleAdd
		*/
		void CacheMultiply( CSIBCVector4D & i_vResult, const CSIBCVector4D & i_vVector);

		/*!	Playstation 2 specific. Right-multiplies the input vector \p i_vVector by the last
			cached matrix (See CSIBCMatrix4x4::CacheMatrix). The resulting vector is then scaled
			by \p i_fScale. The operation is as follows: <TT>Vout = (Vin * Mcache) * i_fScale</TT>.

			\param[in]	i_vResult	Stores the result of the matrix-product.
			\param[in]	i_vVector	The vector to be multiplied.
			\param[in]	i_fScale	The amount to scale the resulting vector by.

			\sa	CSIBCMatrix4x4::CacheMatrix
			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector3D &, const CSIBCVector3D &)
			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector4D &, const CSIBCVector4D &)
			\sa CSIBCMatrix4x4::CacheMultiplyScaleAdd
		*/
		void CacheMultiplyScale( CSIBCVector3D & i_vResult, CSIBCVector3D & i_vVector, float i_fScale );

		/*!	Playstation 2 specific. Right-multiplies the input vector \p i_vVector by the last
			cached matrix (See CSIBCMatrix4x4::CacheMatrix). The resulting vector is then scaled
			by \p i_fScale, and finally the result vector is added to this vector. The operation
			is as follows: <TT>Vio' = [(Vin * Mcache) * i_fScale] + Vio</TT>.

			\param[in,out]	io_vResult	Vector to add to the resulting scaled vector-matrix.
					Stores the result of the matrix-product on output.
			\param[in]	i_vVector	The vector to be multiplied.
			\param[in]	i_fScale	The amount to scale the resulting vector by.

			\sa	CSIBCMatrix4x4::CacheMatrix
			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector3D &, const CSIBCVector3D &)
			\sa CSIBCMatrix4x4::CacheMultiply( CSIBCVector4D &, const CSIBCVector4D &)
			\sa CSIBCMatrix4x4::CacheMultiplyScale
		*/
		void CacheMultiplyScaleAdd( CSIBCVector3D & io_vResult, CSIBCVector3D & i_vVector, float i_fScale );
#endif

		// Operators

		/*! Computes the matrix-product between this matrix and \p i_mMatrix. This matrix is
			right-multiplied by the input matrix, thus the operation is as follows:
			<TT>Mout = Mthis * Minput</TT>.

			\param[in]	i_mMatrix	The matrix to multiply this matrix by.
			\return	Resulting matrix multiplication.

			\sa CSIBCMatrix4x4::Multiply(CSIBCMatrix4x4&, CSIBCMatrix4x4&)
			\sa	CSIBCMatrix4x4::Multiply(CSIBCMatrix4x4&)
		*/
        CSIBCMatrix4x4		operator*(CSIBCMatrix4x4 & i_mMatrix);


		/*! Computes the matrix-product between this matrix and the row vector \p i_vVector. The \c Z and
			\c W values of the vector (to make the multiplication possible) are assumed to be \c 0.0f and
			\c 1.0f, respectively. The vector is right-multiplied by this matrix, thus the operation is
			as follows: <TT>Vout = Vin * Mthis</TT>.

			\param[in]	i_vVector		Row vector to multiply with this matrix.
			\return	Resulting vector from the multiplication.

			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector2D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector4D&)
		*/
        CSIBCVector4D		operator*(CSIBCVector2D & i_vVector);

		/*! Computes the matrix-product between this matrix and the row vector \p i_vVector. The \c W value
			of the vector (to make the multiplication possible) is assumed to be \c 1.0f. The vector is
			right-multiplied by this matrix thus the operation is as follows: <TT>Vout = Vin * Mthis</TT>.

			\param[in]	i_vVector		Row vector to multiply with this matrix.
			\return	Resulting vector from the multiplication.

			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector2D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector4D&)
			\sa	CSIBCMatrix4x4::Multiply(CSIBCVector3D&, const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::MultiplyLeft
		*/
        CSIBCVector4D		operator*(CSIBCVector3D & i_vVector);

		/*! Computes the matrix-product between this matrix and the row vector \p i_vVector. The vector is
			right-multiplied by this matrix thus the operation is as follows: <TT>Vout = Vin * Mthis</TT>.

			\param[in]	i_vVector		Row vector to multiply with this matrix.
			\return	Resulting vector from the multiplication.

			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector2D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector3D&)
			\sa	CSIBCMatrix4x4::Multiply(const CSIBCVector4D&)
			\sa CSIBCMatrix4x4::operator*(CSIBCVector4D&)
		*/
        CSIBCVector4D		operator*(CSIBCVector4D & i_vVector);

		/*! Assigns the values in \p i_mMatrix to this matrix.
			\param[in]	i_mMatrix	Matrix to copy data from.
			\return	Reference to this matrix.
			\sa	CSIBCMatrix4x4::Set
			\sa	CSIBCMatrix4x4::operator+=
		*/
        CSIBCMatrix4x4&		operator = (const CSIBCMatrix4x4 & i_mMatrix);

		/*! Adds this matrix and \p i_mMatrix and stores the result in this matrix.

			\param[in]	i_mMatrix	Matrix to add this matrix to.
			\return	Reference to this matrix.
			\sa	CSIBCMatrix4x4::operator=
			\sa CSIBCMatrix4x4::Multiply
		*/
		CSIBCMatrix4x4&		operator +=( const CSIBCMatrix4x4 & i_mMatrix);

		/*! Not implemented yet. */
		SI_Error Dump();

		/*! Not implemented yet. */
        SI_Error SelfTest();

	private:

#ifdef _PSX2
		sceVu0FMATRIX	m_Matrix;
		float			*row1;
		float			*row2;
		float			*row3;
		float			*row4;
#else
		SI_Matrix 		m_Matrix;
#endif

};

#endif
// CSIBCMatrix
