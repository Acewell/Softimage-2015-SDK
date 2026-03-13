//***************************************************************************************
// File supervisor: Crosswalk team
/*!
	\file SIBCSearchPath.h
	\brief Defines the CSIBCSearchPath class

	Copyright 2008 Autodesk, Inc.  All rights reserved.
	Use of this software is subject to the terms of the Autodesk license agreement
	provided at the time of installation or download, or which otherwise accompanies
	this software in either electronic or hard copy form.
*/
//***************************************************************************************

//***************************************************************************************
// Defines
//***************************************************************************************
#ifndef __CSIBCSearchPath_H__
#define __CSIBCSearchPath_H__

//***************************************************************************************
// Includes
//***************************************************************************************
#include <SIBCArray.h>
#include <SIBCString.h>
#include <SIBCUtil.h>

//***************************************************************************************
// CSIBCSearchPath | deals with paths and filenames
//***************************************************************************************

/*!	\brief Class dealing with paths and filenames.

	This class provides an easy method for locating files within designated search paths
*/

class XSICOREEXPORT CSIBCSearchPath
{
	public:

		/*!	Default Constructor.
			Initializes a CSIBCSearchPath object.
		*/
		CSIBCSearchPath();

		~CSIBCSearchPath();

		/*! Adds a search path to this object. Subsequent calls to CSIBCSearchPath::Search,
			and CSIBCSearchPath::GetFiles will look in this path for matching files.
			\param[in]	in_Path	String containing the full path.
			\retval SI_Error::SI_SUCCESS The search path was added successfully.
			\sa CSIBCSearchPath::GetPaths
			\sa CSIBCSearchPath::ClearPaths
		*/
		SI_Error AddPath( CSIBCString & in_Path);

		/*!	Clears all search paths associated with this object.
			\retval SI_Error::SI_SUCCESS The search path was added successfully.
			\sa CSIBCSearchPath::AddPath
			\sa CSIBCSearchPath::GetPaths
		*/
		SI_Error ClearPaths();

		/*! Searches for a file named \p file, in the search paths added with CSIBCSearchPath::AddPath.
			\param[in]	file		Filename to search for.
			\param[out]	resultpath	Contains the full path and filename of the file, if found.
			\retval SI_Error::SI_SUCCESS The file was located. \p resultpath contains the path and filename.
			\retval SI_Error::SI_FILE_NOT_FOUND The file could not be found (\p resultpath is unchanged).
			\sa CSIBCSearchPath::GetFiles
			\sa CSIBCSearchPath::AddPath
			\sa CSIBCSearchPath::GetPaths
		*/
		SI_Error Search( CSIBCString &file, CSIBCString &resultpath );

		/*! Returns an array of all files matching \p in_Filter in the search paths for this object.
			This function will also return any directories matching the search filter.
			\param[in]	in_Filter	The filename to search for (can include wildcards).
			\param[out]	out_pFiles	Pointer to an array of strings to append the full paths and filenames
				of files matched to \p in_Filter in this object's search paths.	The strings added
				to this array must be freed by the caller.
			\retval SI_Error::SI_SUCCESS The command was successful.
			\sa CSIBCSearchPath::GetDirectories
			\sa CSIBCSearchPath::Search
			\sa CSIBCSearchPath::AddPath
			\sa CSIBCSearchPath::GetPaths
		*/
		SI_Error GetFiles( CSIBCString &in_Filter, CSIBCArray < CSIBCString * >	*out_pFiles );


		/*! Exactly like GetFiles, except that only directories matching the filter are returned.
			\param[in]	in_Filter	The filename to search for (can include wildcards).
			\param[out]	out_pDirs	Pointer to an array of strings to append the full paths of directories
				matched to \p in_Filter in this object's search paths.	The strings added
				to this array must be freed by the caller.
			\retval SI_Error::SI_SUCCESS The command was successful.
			\sa CSIBCSearchPath::GetFiles
			\sa CSIBCSearchPath::Search
			\sa CSIBCSearchPath::AddPath
			\sa CSIBCSearchPath::GetPaths
		*/
		SI_Error GetDirectories( CSIBCString& in_Filter, CSIBCArray < CSIBCString * > * out_pDirs );


		/*! Returns the array containing the search paths defined for this object.
			\return	Reference to the array containing the search paths for this object.
			\sa CSIBCSearchPath::AddPath
			\sa CSIBCSearchPath::ClearPaths
		*/
		CSIBCArray < CSIBCString * > &GetPaths() { return m_Paths; };	// Get the paths


	protected:


	private:
		CSIBCArray < CSIBCString * >	m_Paths;
		SI_Void							*m_pUnused;

};


#endif // CSIBCSearchPath
