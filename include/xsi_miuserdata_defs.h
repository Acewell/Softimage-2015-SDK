/*! \file xsi_miuserdata_defs.h
    \brief Softimage mental ray userdata defines.
	@devnote Compatibility with C is required. Tab space is 4.

    The file defines the magic numbers and structures required to query and access
	for userdata passed to a mental ray shader by Softimage.
*/
#ifndef XSI_MIUSERDATA_DEFS_H
#define XSI_MIUSERDATA_DEFS_H

#include <shader.h>

/* Transformation data ------------------------------------------*/

#define XSIMR_INSTANCETRANSFORMDATA_LABEL	0x00004210
#define XSIMR_INSTANCETRANSFORMDATA_VERSION	0x00000003

#define XSIMR_SHADOWINSTANCE_LABEL			0xf6a209ca		// From random.org

typedef enum
{
	E3DIF_Ignore		= 0,
	E3DIF_Back			= 1,
	E3DIF_Front			= 2,
	E3DIF_Both			= 3
} xsimrInstanceFaceFlags;

#define miDONTCARE			(miCBoolean)2

typedef struct
{
	miCBoolean				is_instance;

	miCBoolean				primary_visible;

	miCBoolean				transparent_receive;
	miCBoolean				transparent_cast;

	miCBoolean				reflection_receive;
	miCBoolean				reflection_cast;

	miCBoolean				refraction_receive;
	miCBoolean				refraction_cast;

	miCBoolean				fg_receive;
	miCBoolean				fg_cast;
	miCBoolean				fg_visible;

	miCBoolean				gi_receive;
	miCBoolean				gi_cast;
	miCBoolean				gi_visible;

	miCBoolean				caustic_receive;
	miCBoolean				caustic_cast;
	miCBoolean				caustic_visible;

	miCBoolean				shadow_receive;
	miCBoolean				shadow_cast;

	xsimrInstanceFaceFlags	face;
} xsimrInstanceFlags;

typedef struct
{
	miVector				scaling;
	miVector				translation;
	miQuaternion			rotation;
	miQuaternion			scale_orientation;
} xsimrInstanceTransform;

typedef struct
{
	miUint4					version;			// Version + Byteswap indicator
	miCBoolean				si_scaling;			// Perform SI scaling (as opposed to classical)
	miCBoolean				motionblur;			// Do motion blur
	xsimrInstanceFlags		flags;				// Instance's visibility flags
	xsimrInstanceTransform	open_transform;		// Instance's transform on shutter open
	xsimrInstanceTransform	close_transform;	// Instance's transform on shutter close (or if no motion blur)
} xsimrInstanceTransformData;


/* -----------------------------------------------------------*/
/*! \defgroup LightAttributes Light Attribute Define
	In Softimage, you can set lights to affect different portions of the lighting calculation.
	Normally, a lighting model, such as Phong, computes a diffuse component and a
	specular component as part of the lighting calculation. However, users can specify
	that a light should not contribute to the diffuse component. All four combinations
	(diffuse light, specular light, both, neither) are acceptable.

	To pass this information to the shaders, Softimage associates a piece of user data
	with the light. The shader can then extract this user data from the light,
	and perform the appropriate calculations.

	To find the user data, the shader must ask for the head of the list of user data
	associated with the light. The shader then searches through this list for the
	user data with the magic number \c XSIMR_LIGHTDATA_LABEL. If it finds it,
	it extracts the settings using the xsimrLightData struct. If it does
	not find the data, it implies that both specular and diffuse computations
	should be performed.

	\sa xsimrLightFlags, xsimrLightData
	\since 7.0
@{
*/
#define XSIMR_LIGHTDATA_LABEL		2860411				/*!< The magic number for querying light userdata from a mental ray shader. */
/*! @}

	\defgroup xsimrLightFlags xsimrLightFlags Enum
	Determines which computation should be performed based on the magic number ::XSIMR_LIGHTDATA_LABEL.
	\sa \ref LightAttributes, \ref xsimrLightFlags
	\sa \ref LightAttributes, xsimrLightData
	\since 7.0
@{
*/
typedef enum
{
	XSIMR_LF_DIFFUSE			= 1 << 0,				/*!< Calculate the diffuse component. */
	XSIMR_LF_SPECULAR			= 1 << 1				/*!< Calculate the specular component. */
} xsimrLightFlags;
/*! @}

	\brief Stores information about whether the diffuse and specular are applied.
	\sa \ref LightAttributes, \ref xsimrLightFlags
	\since 7.0
@{
*/
typedef struct
{
	xsimrLightFlags				flags;	 /*!< A flag determining if the diffuse and specular are applied. */
} xsimrLightData;

/* -----------------------------------------------------------*/
/*! \defgroup xsimrLightIllumData Light Illumination Data
	In mental ray, light shaders usually return a combined
	light color and shadowing information. To get a separated
	information from the light, a shader calling the light
	sampling functions can initialise this structure and
	pass it to the light shader using \c mi_shaderstate_set
	with the key value of \c XSIMR_LIGHTILLUMDATA_KEY.
	The light shader, if successful, will fill in the appropriate
	information in the structure.
	\since 8.0 (2010)
@{
*/
#define XSIMR_LIGHTILLUMDATA_KEY		"xsiLID"		/*!< The key value to use to attach the data structure to the shader state */

/*! \brief If set by a shader, will be filled in by Softimage's light shaders
		to contain a separated light and shadow information. Also contains
		the amount of contribution this light gives to the diffuse and specular
		components of the shading model.
	\sa \ref xsimrLightFlags
	\since 8.0 (2010)
*/
typedef struct
{
	miUint		struct_size;		/*!< Set to sizeof() struct, for versioning */

	miBoolean	set;				/*!< Values were set by the light */

	miScalar	diffuse;			/*!< Diffuse contribution */
	miScalar	specular;			/*!< Specular contribution */

	miColor		color;				/*!< Light color without shadow. */
	miColor		shadow;				/*!< Shadow color. Multiply with the light color to get final value. */
} xsimrLightIllumData;

/* -----------------------------------------------------------*/
/*! \defgroup RenderMapDefine RenderMap Define
	\note For future use.
	\since 7.0
@{
*/
#define XSIMR_RENDERMAPDATA_LABEL		0x2C1ACA		/*!< The magic number for querying rendermap userdata from a mental ray shader. */


/* Profile Curves ---------------------------------------------*/
#define XSIMR_PROFILECURVEDATA_LABEL		0x9FDDD497; // random.org

/*! \defgroup xsimrCurveExtrapolation xsimrCurveExtrapolation Enum
	Extrapolation methods used for evaluating the curve before and after the end points.
	\sa xsimrProfileCurveData
	\since 7.0
@{
*/
typedef enum
{
	XSIMR_CE_CONSTANT			= 1,	/*!< The values of the end points extend to infinity */
	XSIMR_CE_END_GRADIENT		= 2,	/*!< The end segments extend to infinity */
	XSIMR_CE_CYCLE				= 3,	/*!< The curve cycles indefinitely in both directions, each curve starting on the same value */
	XSIMR_CE_CYCLE_RELATIVE		= 4		/*!< The curve cycles indefinitely in both directions, but each curve after the original starts on the
										 end point of the previous curve, and each curve before ends on the start point of the next. */
} xsimrCurveExtrapolation;

/*! \brief A profile curve data sampled into linear segments.

	This profile curve data represents a sampled profile curve from a shader's f-curve
	parameter. The curve is sampled to a tolerance of \c 1/1000 and so should provide enough
	data without showing any banding in the final render, if used as a ramp.
	The extrapolation type indicates how to evaluate the curve before and after the end
	points of the curve. See ::xsimrCurveExtrapolation for more information.

	\sa ::xsimrCurveExtrapolation
	\since 7.0
*/
typedef struct {
	xsimrCurveExtrapolation	extrapolation_type;		/*!< Extrapolation method. */
	miInteger				n_points;				/*!< Number of points on the curve. */
	miVector2d				points[ 1 ];			/*!< An array of profile curve sample points. */
} xsimrProfileCurveData;


/* Particle Shape -----------------------------------------------------------*/
#include <shader.h>
#include <geoshader.h>

#define XSIMR_POINTCLOUDDATA_LABEL			0x613EC66E		// random.org

#define XSIMR_POINTCLOUDDATA_VERSION		0x020000		// 2.0

/*! xsimrParticleShapeType xsimrParticleShapeType Enum
	Defines the particle shape types for rendering.
	\sa xsimrParticleShape, xsimrPointCloudData, xsimrAttributeData
	\since 7.0
@{
*/
typedef enum
{
	xsimrSHAPE_POINT,				/*!< Point type. */
	xsimrSHAPE_SEGMENT,				/*!< Segment type. */
	xsimrSHAPE_DISC,				/*!< Disc type. */
	xsimrSHAPE_RECTANGLE,			/*!< Rectangle type. */
	xsimrSHAPE_SPHERE,				/*!< Sphere type. */
	xsimrSHAPE_BOX,					/*!< Box type. */
	xsimrSHAPE_CYLINDER,			/*!< Cylinder type. */
	xsimrSHAPE_CAPSULE,				/*!< Capsule type. */
	xsimrSHAPE_CONE,				/*!< Cone type. */
	xsimrSHAPE_BLOB,				/*!< Blob type. */
	xsimrNB_SIMPLE_SHAPES,			/*!< Simple shape type. */

	xsimrSHAPE_INSTANCE		= 128,	/*!< Instance type. */
} xsimrParticleShapeType;
/*! @}

	\brief Particle shape structure

	The data pointed to by each data tag is a flat list of particle attributes
	for each particle in the cloud. The size of each attribute entry is dependent
	upon the parameter type in xsimrAttributeData::type.

	\sa ::xsimrParticleShapeType, xsimrAttributeData, xsimrPointCloudData
	\since 7.0

	\eg Example for how to use the particle data structure:
	\code
		xsimrPointCloudData *findParticleData( miState *state )
		{
			if( state->instance == miNULLTAG )
				return( NULL );

			// Get the item tag and the item’s userdata block tag.
			miTag       object_tag;
			mi_query(miQ_INST_ITEM, NULL, state->instance, (void *)&object_tag);

			if( object_tag == miNULLTAG )
				return ( NULL );

			miTag       data_tag;
			mi_query(miQ_OBJ_DATA, NULL, object_tag, (void *)&data_tag );

			while( data_tag )
			{
				miUint      label = 0;

				mi_query( miQ_DATA_LABEL, NULL, data_tag, &label );

				if( label == XSIMR_POINTCLOUDDATA_LABEL )
				{
					xsimrPointCloudData     *data_ptr = NULL;

					mi_query( miQ_DATA_PARAM, NULL, data_tag, (void *)&data_ptr );

					if( data_ptr->version != XSIMR_POINTCLOUDDATA_VERSION )
					{
						mi_error( "Unsupported point cloud data version (%d.%d)", data_ptr->version >> 16, data_ptr->version & 0xFFFF );
						return( NULL );
					}

					return( data_ptr );
				}

				mi_query(miQ_DATA_NEXT, NULL, data_tag, &data_tag);
			}
			return( NULL );
		}

		static void *findAttribute
		(
			xsimrPointCloudData *data_ptr,
			const char      *name_wanted,
			xsimrAttributeType type_wanted,
			miBoolean       *is_constant
			)
		{
			for( int i = 0; i < data_ptr->n_data; i++ )
			{
				xsimrAttributeData  *attrib_ptr = &data_ptr->attributes[ data_ptr->i_data + i ];
				const char*      attrib_name = (const char *)mi_db_access( attrib_ptr->name );
				mi_db_unpin( attrib_ptr->name );

				if( _stricmp( attrib_name, name_wanted ) == 0 &&
					attrib_ptr->type == type_wanted )
				{
					void    *attrib_data_ptr;

					*is_constant = attrib_ptr->constant;

					mi_query( miQ_DATA_PARAM, NULL, attrib_ptr->data, &attrib_data_ptr );

					return( data_ptr );
				}
			}

			return( NULL );
		}

		// Get position vector and "size" attribute from cloud
		void get_my_data
		(
			miState         *state,
			miVector        **pos_ptr,
			miScalar        **radius_ptr,
			miBoolean       *radius_const
			)
		{
			xsimrPointCloudData *data_ptr;

			data_ptr = findParticleData( state );
			if( !data_ptr )
				return;

			// Get the position vector.
			mi_query( miQ_DATA_PARAM, NULL, data_ptr->positions, (void *)pos_ptr );

			findAttribute( data_ptr, "Radius", xsimrATTRIBUTE_SCALAR, radius_const );
		}
	\endcode
*/
typedef struct
{
	xsimrParticleShapeType		type;			/*!< The particle shape type. */
	miInteger					instance_id;	/*!< If the shape type is xsimrSHAPE_INSTANCE, then
													 this index into the instance list on the pointcloud
													 geometry shader's parameter structure */
} xsimrParticleShape;


/*! \brief Particle data blob structure
	\sa ::xsimrParticleShapeType, xsimrAttributeData, xsimrPointCloudData
	\since 8.0 (2010)
	\endcode
*/
typedef struct
{
	miUint						size;		/*!< Size of data in bytes */
	miUint						offset;		/*!< Offset, in bytes, into the data array given in xsimrAttributeData where the blob data starts */
} xsimrParticleBlob;

/*! \defgroup xsimrAttributeType xsimrAttributeType Enum
	Defines the attribute data types for the particle data.
	\sa xsimrAttributeData, xsimrPointCloudData, xsimrParticleShape
	\since 7.0
@{
*/
typedef enum
{
	xsimrATTRIBUTE_BOOLEAN,		/*!< Maps to \c miCBoolean mental ray native data type */
	xsimrATTRIBUTE_INTEGER,		/*!< Maps to \c miInteger  mental ray native data type */
	xsimrATTRIBUTE_SCALAR,		/*!< Maps to \c miScalar  mental ray native data type */
	xsimrATTRIBUTE_VECTOR2,		/*!< Maps to \c miVector2d  mental ray native data type */
	xsimrATTRIBUTE_VECTOR3,		/*!< Maps to \c miVector  mental ray native data type */
	xsimrATTRIBUTE_VECTOR4,		/*!< Maps to \c miQuaternion  mental ray native data type */
	xsimrATTRIBUTE_QUATERNION,	/*!< Maps to \c miQuaternion  mental ray native data type */
	xsimrATTRIBUTE_MATRIX33,	/*!< Maps to \c 3 \c x \c miVector  mental ray native data type */
	xsimrATTRIBUTE_MATRIX44,	/*!< Maps to \c miMatrix  mental ray native data type */
	xsimrATTRIBUTE_COLOR4,		/*!< Maps to \c miColor  mental ray native data type */
	xsimrATTRIBUTE_ROTATION,	/*!< Maps to \c miVector  mental ray native data type (Euler angles in radians) */
	xsimrATTRIBUTE_SHAPE,		/*!< Maps to \c xsimrParticleShape structure */
	xsimrATTRIBUTE_BLOB,		/*!< Maps to \c xsimrParticleBlob structure */
} xsimrAttributeType;
/*! @}

	\brief A structure containing the information for a single attribute.

	Each attribute has a name and a type. The tag points to a miUserdata blob that contains a
	flat array of xsimrPointCloudData::nb_particles attribute values.

	\note If the xsimrAttributeData::constant flag is \c miTRUE, then all the attribute entries
	are the same value and therefore only the first attribute entry is valid to conserve space.

	\sa ::xsimrAttributeType, xsimrPointCloudData, xsimrParticleShape
	\since 7.0

	\eg Example demonstrating how to use the xsimrAttributeData structure
	\code
		miScalar getSizeAtIndex( siParticleAttribute *attr, miUint pid, miUint index )
		{
			miUserdata		*data_ptr;
			miScalar		*size_ptr;
			miScalar		result;

			if( index >= attr->count )
				index = attr->count - 1;

			data_ptr = (miUserdata *)mi_db_access( attr->tag );
			size_ptr = (miScalar *)&data_ptr->parameters[ 0 ];
			if( attr->constant )
				result = size_ptr[ 0 ];
			else
				result = size_ptr[ pid * attr->count + index ];

			mi_db_unpin( attr_size->tag );

			return( result );
		}
	\endcode
*/
typedef struct
{
	/*! The name of the attribute. The name is case-insensitive.
	*/
	miTag			name;			// The attribute's name

	/*! The value type of the data. See ::xsimrAttributeType for which mental ray native data
		types each enumeration type maps to.
	*/
	xsimrAttributeType	type;	// The attribute's data type

	/*! The constant flag of the data. If all the values of an attribute are the same, then
		the data is considered to be constant and only one value is stored, which should be
		used for all points in the cloud. In case of arrays, the same array is used for all
		points, rather than all values of the array being the same.

		\note If this value is \c miTRUE then the userdata blob pointed to by xsimrAttributeData::data
		will contain only a single value, or a single array of values, and xsimrAttributeData::offsets,
		if defined, will contain only two indices.
	*/
	miBoolean		constant;

	/*! The size of the data type in bytes. This is equal to the result of the \c sizeof operator on
		the mental ray data type used to store the data (see ::siParticleAttributeType).
	*/
	miUint			size;

	/*! The userdata tag for the array offset indices of type \c miUint32. If the data is
		an array of arrays, then this index list will give the index into the data list for
		the given particle. This list is one entry larger than the number of particles so
		that the length can always be calculated by <TT>( offset[ id + 1 ] - offset[ id ] )</TT>
		for each particle. If the data is constant, and that data is an array of arrays, then
		this list will contain two entries.
	*/
	miTag			offsets;

	/*! The userdata tag to the actual value data storage. If the xsimrAttributeData::offsets
		tag is an \c miNULLTAG then there is only one single value per particle. Otherwise the
		data comes in contiguous value chunks for each particle, and the contents of the offsets
		data can be used to index into it for each particle.
	*/
	miTag			data;			// The userdata tag for the data blob.

	/*! A tag to a string that contains the blob type name if the \c type field is set to
		::xsimrATTRIBUTE_BLOB. For any other type, it is left as a \c miNULLTAG.
		\since 2010 (8.0)
	*/
	miTag			blob_type;
} xsimrAttributeData;


/*! \brief The main particle data header.

	This structure contains the version of the data as the first entry (always), the cloud's bbox,
	number of particles in the cloud, the position vector and any optional attributes that were
	defined on the cloud.

	The position data holds an array of \c miVector values that represent each particle's position
	in local space. The number of entries in that array equals xsimrPointCloudData::nb_particles.
	The number of entries in the data array of each particle attribute is the same, unless the data
	is constant. In the case of constant data, only the first entry is valid and should be used for
	each particle.	The position array is always full, never constant.

	\sa xsimrPointCloudData, xsimrPointCloudIndex, ::PointCloudDefines, xsimrAttributeData, xsimrParticleShape
	\since 7.0
*/
typedef struct
{
	miUint			version;			/*!< Version of the data */
	miUint			nb_particles;		/*!< Number of particles in the cloud */
	miTag			positions;			/*!< Particle position in local space */

	int				i_data;				/*!< Data index */
	int				n_data;				/*!< Data count */

	xsimrAttributeData attributes[ 1 ];	/*!< Attributes (optional) defined on the cloud */
} xsimrPointCloudData;


// Instance Marker

/*! \defgroup PointCloudDefines PointCloud Defines
	There are two PointCloud Defines:
	\li \ref XSIMR_POINTCLOUD_INDEX_LABEL
	\li \ref XSIMR_ATTRIBUTE_SHADER_KEY

	\sa xsimrPointCloudData, xsimrAttributeData, xsimrParticleShape
	\since 7.0
@{
*/
#define XSIMR_POINTCLOUD_INDEX_LABEL		0x613EC66F		/*!< PointCloud index label. */
#define XSIMR_ATTRIBUTE_SHADER_KEY			"xsiATTR"		/*!< Attribute shader key. */
/*! @}

	\brief Stores the PointCloud index.

	\sa xsimrPointCloudData, xsimrAttributeData, xsimrParticleShape
	\since 7.0
@{
*/
typedef struct
{
	miUint			pc_index;	/*!< PointCloud index */
	miUint			st_index;	/*!< Strand Point index */
} xsimrPointCloudIndex;
/*! @}*/


// Time mapping data for attribute time-controlled images
/*! \brief A single range to frame mapping entry.

	The minimum and maximum values of the range are both inclusive.

	\sa xsimrAttributeImageTimeMap, xsimrAttributeData, xsimrParticleShape, xsimrPointCloudData
	\since 7.0
*/
typedef struct
{
	miScalar			range_min;		/*!< Minimum value for range */
	miScalar			range_max;		/*!< Maximum value for range */
	miInteger			index;			/*!< Index */
} xsimrTimeMapValue;

/*! \brief List of range to frame mapping values.

	This is used to map attribute value ranges to individual frames of an image sequence.

	\sa xsimrTimeMapValue, xsimrAttributeData, xsimrParticleShape, xsimrPointCloudData
	\since 7.0
*/
typedef struct
{
	miInteger			n_time_map;			/*!< Index of attribute value */
	xsimrTimeMapValue	time_map[ 1 ];		/*!< Single range to frame mapping entry */
} xsimrAttributeImageTimeMap;

////////////////////////////////////////////////////////////////////////////////
// Color Correction Look-up Table Definition

#define XSIMR_CCLUT_GAMMA_LABEL		0x0A63EC03	// random.org
#define XSIMR_CCLUT_1D_LABEL		0x0F2F2674	// random.org
#define XSIMR_CCLUT_3D_LABEL		0x088F67E5	// random.org

typedef struct
{
	miScalar		r, g, b;
} xsimrColor3;

typedef struct
{
	miScalar		red_gamma;
	miScalar		green_gamma;
	miScalar		blue_gamma;
} xsimrCCLUTGamma;

typedef struct
{
	miScalar		from;
	miScalar		to;
} xsimrCCLUTMapTuple;

typedef struct
{
	int				i_tuple;
	int				n_tuple;
	xsimrCCLUTMapTuple tuple[ 1 ];
} xsimrCCLUTRangeMap;

typedef struct 
{
	miTag			name;
	miTag			params;
} xsimrCCLUTPreTransform;

typedef struct
{
	xsimrCCLUTRangeMap	red_range;
	xsimrCCLUTRangeMap	green_range;
	xsimrCCLUTRangeMap	blue_range;

	int				i_lut;
	int				n_lut;
	xsimrColor3		lut[ 1 ];

	xsimrCCLUTPreTransform pretransform;
} xsimrCCLUT1D;

typedef struct
{
	xsimrCCLUTRangeMap	red_range;
	xsimrCCLUTRangeMap	green_range;
	xsimrCCLUTRangeMap	blue_range;

	// red_size * green_size * blue_size == n_lut
	int				red_size;
	int				green_size;
	int				blue_size;

	int				i_lut;
	int				n_lut;
	xsimrColor3		lut[ 1 ];

	xsimrCCLUTPreTransform pretransform;
} xsimrCCLUT3D;


#define XSIMR_MESHDATA_LABEL			0x112A61FF		// random.org
#define XSIMR_MESHDATA_VERSION			0x010000		// 1.0

typedef enum
{
	xsimrMESHATTRIBUTESTORAGE_CONSTANT,	
	xsimrMESHATTRIBUTESTORAGE_TSPACE,
} xsimrMeshAttributeStorage;

/*! \brief A structure representing an ICE attribute on a mesh.

	\sa xsimrMesh, xsimrMeshAttributeStorage
	\since 2012
*/
typedef struct
{
	char						name[256];	// A string with the attribute name
	xsimrAttributeType			type;		// The attribute type. For constant storage, constant_data contains the per mesh value.
	xsimrMeshAttributeStorage	storage;	// The attribute storage. Attributes can be defined as tspace, per vertex userdata or constant.
	miInteger					id;			// The index for tspace or vertex user data storage.

	// A union for the constant data.
	union 
	{
		miCBoolean		b;
		miInteger		i;
		miScalar		s;
		miVector2d		v2;
		miVector		v3;
		miQuaternion	v4;
		miVector		m33[3];
		miMatrix		m44;
		miColor			c;
	} constant_data;

} xsimrMeshAttribute;

/*! \brief A user data applied on meshes.

	This is used to map ICE attribute names to tspace, userdata or constant.

	\sa xsimrMeshAttribute, xsimrMeshAttributeStorage
	\since 2012
*/
typedef struct
{
	// An array of xsimrMeshAttribute that represents the pushed attributes
	int	i_attributes;
	int	n_attributes;
	xsimrMeshAttribute attributes[ 1 ];
} xsimrMesh;

#endif /* XSI_MIUSERDATA_DEFS_H */
