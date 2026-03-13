//*****************************************************************************
/*!
   \file xsi_griddata.h
   \brief GridData class declaration.

	Copyright 2008 Autodesk, Inc.  All rights reserved.  
	Use of this software is subject to the terms of the Autodesk license agreement 
	provided at the time of installation or download, or which otherwise accompanies 
	this software in either electronic or hard copy form.   
*/
//*****************************************************************************

#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif

#ifndef __XSIGRIDDATA_H__
#define __XSIGRIDDATA_H__

#include <xsi_base.h>
#include <xsi_ppgitem.h>
#include <xsi_value.h>
#include <xsi_bitarray.h>

namespace XSI {
struct CColor ;
//*****************************************************************************
/*! \class GridData xsi_griddata.h
	\brief This object represents a 2-dimensional array of data.  The word \a Grid refers to the visual presentation
	of 2-Dimensional data on a grid control (sometimes called a table or spreadsheet control).  The word \a Cell refers
	to a single element of the array.

	The dimensions of the array can be dynamically resized and many types of data can be stored as Cell data.  The
	Columns and Rows can be labeled and it is possible to refer to the data by these label strings rather than by indices.

	Each cell in the %GridData is a CValue object, so strings, integers, doubles and many other types of data can be
	stored in the %GridData. However not all data types may be properly displayed in the associated User Interface.  Also,
	although it is possible to store object references (as CRef objects) inside a %GridData, these cannot be persisted so
	it is better to store the SIObject::GetFullName as the cell value.

	There are three main uses for the %GridData object:

		\par Data for a ::siGridControl on a custom object (see CustomProperty::AddGridParameter)
			In this case the user can view and edit the data and the data is saved inside the scene along with the
			CustomProperty.  This can be  an effective way to store lists, vectors or even arrays of vectors related
			to a plug-in.  Some aspects of the visual representation of the %GridData object are set directly on the
			%GridData object (for example GridData::PutColumnType) but most attributes are set inside the PPGLayout
			using PPGItem::PutAttribute.  ::siPPGItemAttributes that apply to the ::siGridControl include
			::siUIGridColumnWidths and ::siUIGridHideRowHeader.

		\par Store hidden data that is intended for internal use by a plug-in
			In this case it is still part of a CustomProperty but it is not exposed to the user, which is easily done
			by not including the %GridData Parameter in the PPGLayout.

		\par Temporary convenience object for dealing with 2-dimensional arrays
			This is most useful for scripting languages like JScript which do not support 2-dimensional arrays, but
			also may be interesting in some cases for C++ developers.  For example, because it employs range checking,
			it is more robust and safe to use when compared with raw pointer-based C++ arrays.

	\sa PPGLayout, CustomProperty, PPG
	\since 4.0

	\eg Demonstrates how to use a %GridData object to display data on a custom object.

	\code
		using namespace XSI;
		Application app ;
		Model root = app.GetActiveSceneRoot(); ;

		CustomProperty prop ;
		root.AddProperty( L"CustomProperty", false, L"GridDataDemo", prop) ;

		// Put two grids on this Custom Property
		Parameter grid1param = prop.AddGridParameter( L"grid1" ) ;
		Parameter grid2param = prop.AddGridParameter( L"grid2" ) ;

		// Unlike basic parameters that have strings, ints or
		// floats as their values, for a Grid parameter the
		// value is an entire GridData object
		GridData grid1 = grid1param.GetValue() ;
		GridData grid2 = grid2param.GetValue() ;

		//
		// The first grid is a typical array of vectors
		//
		grid1.PutColumnCount( 3 ) ;
		grid1.PutRowCount( 4 ) ;

		grid1.PutColumnLabel( 0, L"X" ) ;
		grid1.PutColumnLabel( 1, L"Y" ) ;
		grid1.PutColumnLabel( 2, L"Z" ) ;

		// Fill in some data
		CValueArray gridcontents( grid1.GetRowCount() *
								  grid1.GetColumnCount() ) ;
		gridcontents[0] = 0.0; gridcontents[1]  = 0.5; gridcontents[2]  = 0.2;
		gridcontents[3] = 0.1; gridcontents[4]  = 1.0; gridcontents[5]  = 0.0;
		gridcontents[6] = 1.0; gridcontents[7]  = 1.0; gridcontents[8]  = 9.0;
		gridcontents[9] = 0.3; gridcontents[10] = 0.4; gridcontents[11] = 0.5;
		grid1.PutData(gridcontents) ;

		// Change our mind about the value of the cell at Column 0,
		// row 3
		grid1.PutCell( 0, 3, 99.9 ) ;

		//
		// Setup the second GridData
		// It only has 1 column so it is more like a list than
		// a 2-Dimensional array
		//

		grid2.PutColumnCount( 1 ) ;
		grid2.PutRowCount( 12 ) ;
		grid2.PutColumnLabel( 0, L"Column 0" ) ;
		grid2.PutColumnType( 0, siColumnCombo ) ;

		CValueArray enumInfo( 4 ) ;
		enumInfo[0] = L"Option value 0" ;
		enumInfo[1] = 0l ;
		enumInfo[2] = L"Option value 10" ;
		enumInfo[3] = 10l ;
		grid2.PutColumnComboItems( 0, enumInfo ) ;

		LONG i;
		for ( i = 0 ; i < grid2.GetRowCount() ; i++ )
		{
			grid2.PutRowLabel( i, L"Row " + CValue( i ).GetAsText() ) ;
		}

		//
		// Populate it with some data
		//

		CValueArray items( grid2.GetRowCount() ) ;

		// First two items will use the first item in the combo box
		items[0] = 0l ;
		items[1] = 0l ;

		// rest of the items will select the second option
		for ( i = 2 ; i < items.GetCount() ; i++ )
		{
			items[i] = 10l ;
		}

		grid2.PutColumnValues( L"Column 0", items ) ;


		//
		// Set up some Layout to fine-tune the
		// appearance of the grids
		//

		PPGLayout layout = prop.GetPPGLayout() ;

		PPGItem item = layout.AddItem( L"grid1", NULL, siControlGrid ) ;
		item.PutAttribute( siUIValueOnly, true ) ;

		// We didn't label the rows, so we can hide that column
		item.PutAttribute( siUIGridHideRowHeader, true ) ;



		item = layout.AddItem( L"grid2", NULL, siControlGrid ) ;

		// Specify the width for the row label column and
		// then the data column
		item.PutAttribute( siUIGridColumnWidths, L"100:140" ) ;
		item.PutAttribute( siUIValueOnly, true ) ;

		// Specify a specific height.  This forces the use of
		// a scroll bar
		item.PutAttribute( siUICY, 200l ) ;

		// Make sure that the Column header doesn't get scrolled out
		// of view
		item.PutAttribute( siUIGridLockColumnHeader, true ) ;
	\endcode
*/
//*****************************************************************************

class GridWidget ;

class SICPPSDKDECL GridData : public CBase
{
public:
	/*! Default constructor. */
	GridData();

	/*! Default destructor. */
	~GridData();

	/*! Constructor.
	\param in_ref constant reference object.
	*/
	GridData(const CRef& in_ref);

	/*! Copy constructor.
	\param in_obj constant class object.
	*/
	GridData(const GridData& in_obj);

	/*! Returns true if a given class type is compatible with this API class.
	\param in_ClassID class type.
	\return true if the class is compatible, false otherwise.
	*/
	bool IsA( siClassID in_ClassID) const;

	/*! Returns the type of the API class.
	\return The class type.
	*/
	siClassID GetClassID() const;

	/*! Creates an object from another object.
	\param in_obj constant class object.
	\return The new GridData object.
	*/
	GridData& operator=(const GridData& in_obj);

	/*! Creates an object from a reference object. The newly created object is
	set to empty if the input reference object is not compatible.
	\param in_ref constant class object.
	\return The new GridData object.
	*/
	GridData& operator=(const CRef& in_ref);

	/*! Returns the entire 2-dimensional array of cell data.  The data is represented as a CValueArray, with the data
	organized row by row.
	\return An array containing all the contents of the array.
	*/
	CValueArray GetData() const;

	/*! Sets the content of the entire GridData object with a single call. The array must contain \c Row \c * \c Column
	items, and the data is interpreted to be ordered row by row rather than column by column.
	\warning This call fails if GridData::PutRowCount and GridData::PutColumnCount have not previously been called.
	\param in_items Data to set.
	\return Success or failure of operation.
	*/
	CStatus PutData( const CValueArray& in_items ) ;

	/*! Sets the number of columns contained in the GridData object. It is possible to change the number of columns even
	after data has been assigned to the GridData object.  The value must be greater than zero.
	\param in_val Number of columns for this GridData.
	\return Success or failure of operation.
	*/
	CStatus PutColumnCount( LONG in_val );

	/*! Returns the number of columns contained in the GridData object.
	\return Column count
	*/
	LONG GetColumnCount() const ;

	/*! Sets the number of rows contained in the GridData object. It is possible to change the number of rows even after
	data has been assigned to the GridData object.  The value must be greater than zero.
	\param in_val Number of rows for this GridData.
	\return Success or failure of operation.
	*/
	CStatus PutRowCount( LONG in_val ) ;

	/*! Returns the number of rows contained in the GridData object.
	\return Row count
	*/
	LONG GetRowCount() const ;

	/*! Changes the value of a single element inside the GridData object. The coordinates must be within the valid range
	of the GridData's dimensions.
	\param in_Column 	Column index (zero-based)
	\param in_Row    	Row index (zero-based)
	\param in_CellValue	Value to set in the specified cell
	\return Success or failure of operation.
	*/
	CStatus PutCell(LONG in_Column, LONG in_Row, const CValue& in_CellValue);

	/*! Changes the value of a single element inside the GridData object. In this variation of GridData::PutCell the cell
	is specified by the row and column labels rather than by index.  This is a slightly slower approach but it makes the
	code easier to read. See GridData::PutColumnLabel and GridData::PutRowLabel.
	\param in_ColumnLabel Column label
	\param in_RowLabel    Row label
	\param in_CellValue   Value for the cell
	\return Success or failure of operation.
	*/
	CStatus PutCell(const CString& in_ColumnLabel, const CString& in_RowLabel, const CValue& in_CellValue);

	/*! Returns the value stored on a specific cell of the %GridData object.
	\param in_Column 	Column index (zero-based)
	\param in_Row    	Row index (zero-based)
	\return The contents of the cell.
	\return CValue::m_t==CValue::siEmpty if the cell is empty.
	*/
	CValue GetCell(LONG in_Column, LONG in_Row) const;

	/*! Returns the value stored on the %GridData.

	In this variation of GridData::GetCell the cell is specified by the row and column labels rather than by index.  This
	is a slightly slower approach but it makes the code easier to read.  See GridData::PutColumnLabel and GridData::PutRowLabel.
	\param in_ColumnLabel Column label
	\param in_RowLabel    Row label
	\return The contents of the cell.
	\return CValue::m_t==CValue::siEmpty if the cell is empty.
	*/
	CValue GetCell(const CString& in_ColumnLabel, const CString& in_RowLabel) const;
	/*! Sets values on a single column of a GridData object.
	\param in_Column 		Column index (zero-based)
	\param in_ColumnItems	1-dimensional array of values to set.  The size should be equal to GridData::GetRowCount.
	\return Success or failure of operation.
	*/
	CStatus PutColumnValues( LONG in_Column, const CValueArray & in_ColumnItems );
	/*! Sets values for a single column of a GridData object.
	\param in_ColumnLabel	Column label (see GridData::PutColumnLabel)
	\param in_ColumnItems	1-dimensional array of values to set.  The size should be equal to GridData::GetRowCount.
	\return Success or failure of operation.
	*/
	CStatus PutColumnValues( const CString& in_ColumnLabel, const CValueArray & in_ColumnItems );

	/*! Returns a 1-dimensional array containing all the elements in the requested column.
	\param in_Column Column index (zero-based)
	\return A 1-dimensional array of values from the specified column.  The size is equal to GridData::GetRowCount.
	*/
	CValueArray GetColumnValues(LONG in_Column ) const ;

	/*! Returns a 1-dimensional array containing all the elements in the requested column.
	\param in_ColumnLabel Column label (see GridData::PutColumnLabel)
	\return A 1-dimensional array of values from the specified column.  The size is equal to GridData::GetRowCount.
	*/
	CValueArray GetColumnValues(const CString& in_ColumnLabel ) const ;

	/*! Sets values for a single row of a GridData object.
	\param in_Row		Row index (zero-based)
	\param in_RowItems	1-dimensional array of values to set.  The size should be equal to GridData::GetColumnCount.
	\return Success or failure of operation.
	*/
	CStatus PutRowValues( LONG in_Row, const CValueArray & in_RowItems );

	/*! Sets values for a single row of a GridData object.
	\param in_RowLabel row label (see GridData::PutRowLabel)
	\param in_RowItems 1-dimensional array of values to set.  The size should be equal to GridData::GetColumnCount.
	\return Success or failure of operation.
	*/
	CStatus PutRowValues( const CString& in_RowLabel, const CValueArray & in_RowItems );

	/*! Returns a 1-dimensional array containing all the elements in the requested row.
	\param in_Row Row index (zero-based)
	\return A 1-dimensional array of values from the specified row.  The size is equal to GridData::GetColumnCount.
	*/
	CValueArray GetRowValues(LONG in_Row ) const ;

	/*! Returns a 1-dimensional array containing all the elements in the requested row.
	\param in_RowLabel Row label (see GridData::PutRowLabel)
	\return A 1-dimensional array of values from the specified row.  The size is equal to GridData::GetColumnCount.
	*/
	CValueArray GetRowValues(const CString& in_RowLabel ) const ;

	/*! Sets the label for a Row.  Labels are optional. The visual appearance of row labels can be tweaked with the
	::siUIGridHideRowHeader and ::siUIGridLockRowHeader attributes (see the ::siPPGItemAttribute enum). Once labels
	are specified it is possible to access data via the labels rather than the cell index via functions like
	GridData::PutCell and GridData::GetRowValues.
	\param in_RowIndex Index of the row to label.
	\param in_RowLabel Row label to use.
	\return Success or failure of operation.
	*/
	CStatus PutRowLabel(LONG in_RowIndex, const CString& in_RowLabel );

	/*! Returns the label string of a row.
	\param in_RowIndex Index of the row with the label to get.
	\return The row label.
	\return Empty string if no label has been specified.
	*/
	CString GetRowLabel(LONG in_RowIndex) const;

	/*! Sets the label for a Column.  Labels are optional. The visual appearance of column labels can be tweaked with
	the ::siUIGridHideColumnHeader and ::siUIGridLockColumnHeader attributes (see the ::siPPGItemAttribute enum). Once
	labels are specified it is possible to access data via the labels rather than the cell index via functions like
	GridData::PutCell and GridData::GetColumnValues.
	\param in_ColumnIndex Index of the column to label.
	\param in_ColumnLabel Column label to use.
	\return Success or failure of operation.
	*/
	CStatus PutColumnLabel(LONG in_ColumnIndex, const CString& in_ColumnLabel);

	/*! Returns the label string of a column.
	\param in_ColumnIndex Index of the column with the label to get.
	\return The column label.
	\return Empty string if no label has been specified.
	*/
	CString GetColumnLabel(LONG in_ColumnIndex) const;

	/*! Call this function to signal that a large portion of the GridData contents has changed.  This prevents all updates
	of the user interface associated with the %GridData.  If %GridData is not associated with a GridControl or if the
	Property Page with the GridControl is not being inspected then this call has no effect.  Hence the most likely place
	to use this function is inside logic code (see PPGLayout::PutLogic and PPGLayout::GetLogic).
	\return Success or failure of operation.
	*/
	CStatus BeginEdit();

	/*! Call this function to signal the end of major updates to the %GridData.  At this point all views on the data are
	rebuilt.  For example the user interface may redraw itself.  Each call to GridData::EndEdit should match a previous
	call to GridData::BeginEdit.
	\return Success or failure of operation.
	*/
	CStatus EndEdit();

	/*! Specifies a type of control to use for a particular column. This function is optional because the default column type,
	::siColumnStandard, is suitable for strings, numbers and most other data.
	\param in_ColumnIndex	Index of the column to modify.
	\param in_Type			Type of control (plain data, check box, combo box). See ::siGridWidgetColumnType for a complete
		list of possible control types.
	\return Success or failure of operation.
	*/
	CStatus PutColumnType(LONG in_ColumnIndex, siGridWidgetColumnType in_Type );

	/*! Returns the type of a column (for example ::siColumnCombo or ::siColumnBool).
	\param in_ColumnIndex Index of the column to retrieve.
	\return Type of column control (plain data, check box, combo box). See ::siGridWidgetColumnType for a complete
		list of possible control types.
	*/
	siGridWidgetColumnType GetColumnType( LONG in_ColumnIndex ) const;

	/*! Sets the combo items associated with a column of type ::siColumnCombo. The items are specified in a 1-dimensional
	CValueArray, with a label string and associated integer value for each combo item.  For example the array
	("A", 0, "B", 12) specifies two items for the combo box, one with label "A" and value 0 and the other with label "B"
	and value 12.
	\param in_ColumnIndex Column index (zero based)
	\param in_Items CValueArray containing the label/value pairs
	\return Success or failure of operation.
	*/
	CStatus PutColumnComboItems(LONG in_ColumnIndex, const CValueArray& in_Items);

	/*! Returns the definition of a GridData column having the type ::siColumnCombo.
	\param in_ColumnIndex Column index (zero based)
	\return CValueArray of items in the combo-box.
	\return Empty array if no combo items have been set (see GridData::PutColumnComboItems).
	*/
	CValueArray GetColumnComboItems(LONG in_ColumnIndex);

	/*! Returns a pointer to the user interface control as a GridWidget object. The GridWidget object displays the GridData
	information on a Property Page (PPG object) which allows you to access information about selected cells.
	\note This only returns a valid object when the GridData is actually being inspected.
	\return GridWidget instance representing the GridData's property page currently being inspected.
	*/
	GridWidget GetGridWidget() ;

	/*! Sets the background color on the specified row.
	\return Success or failure of operation.
	\param in_Row Index of the row to color.
	\param in_Color Color to appear in the specified row (as a CColor).
	\return Success or failure of operation.
	\since 5.0
	*/
	CStatus SetRowBackgroundColor( LONG in_Row, const CColor &in_Color );

	/*! Returns the background color of the specified row.
	\param in_Row Index of the row to access.
	\return CColor representing the color that appears in the specified row.
	\since 5.0
	*/
	CColor GetRowBackgroundColor(LONG in_Row );

	/*! Changes a given column's type to siColumnInt.
	\param in_lColumnIndex The column of interest.
	\param in_lMin Minimum valid value.
	\param in_lMax Maximum valid value.
	\param in_lInc Increment that is used while scrubbing.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetIntColumnDef( LONG in_lColumnIndex, LONG in_lMin = INT_MIN, LONG in_lMax = INT_MAX, LONG in_lInc = 1 );

	/*! Retrieves the siColumnInt definition for the given column.
	\param in_lColumnIndex The column of interest.
	\param out_lMin Minimum valid value.
	\param out_lMax Maximum valid value.
	\param out_lInc Increment that is used while scrubbing.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus GetIntColumnDef( LONG in_lColumnIndex, LONG &out_lMin, LONG &out_lMax, LONG &out_lInc ) const;

	/*! Changes a given column's type to siColumnFloat.
	\param in_lColumnIndex The column of interest.
	\param in_dMin Minimum valid value.
	\param in_dMax Maximum valid value.
	\param in_dInc Increment that is used while scrubbing.
	\param in_sDecimal Number of decimals to be displayed.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetFloatColumnDef( LONG in_lColumnIndex, double in_dMin = DBL_MIN, double in_dMax = DBL_MAX, double in_dInc = 1.0, short in_sDecimal = 2 ) ;

	/*! Retrieves the siColumnFloat definition for the given column.
	\param in_lColumnIndex The column of interest.
	\param out_dMin Minimum valid value.
	\param out_dMax Maximum valid value.
	\param out_dInc Increment that is used while scrubbing.
	\param out_sDecimal Number of decimals to be displayed.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus GetFloatColumnDef( LONG in_lColumnIndex, double &out_dMin, double &out_dMax, double &out_dInc, short &out_sDecimal ) const;

	/*! Changes a given column's type to siColumnVector.
	\param in_lColumnIndex The column of interest.
	\param in_sVectorSize Number of components in the vector (2, 3 or 4).
	\param in_dMin Minimum valid value.
	\param in_dMax Maximum valid value.
	\param in_dInc Increment that is used while scrubbing.
	\param in_sDecimal Number of decimals to be displayed.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetVectorColumnDef( LONG in_lColumnIndex, short in_sVectorSize, double in_dMin = DBL_MIN, double in_dMax = DBL_MAX, double in_dInc = 1.0, short in_sDecimal = 2 ) ;

	/*! Retrieves the siColumnVector definition for the given column.
	\param in_lColumnIndex The column of interest.
	\param out_sVectorSize Number of components in the vector (2, 3 or 4).
	\param out_dMin Minimum valid value.
	\param out_dMax Maximum valid value.
	\param out_dInc Increment that is used while scrubbing.
	\param out_sDecimal Number of decimals to be displayed.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus GetVectorColumnDef( LONG in_lColumnIndex, short &out_sVectorSize, double &out_dMin, double &out_dMax, double &out_dInc, short &out_sDecimal ) const;

	/*! Changes a given column's type to siColumnFile.
	\param in_lColumnIndex The column of interest.
	\param in_csBrowseType "File" or "Folder" - determines the browser type to use when double-clicking.
	\param in_csStartupPath Startup directory for file or folder selection.
	\param in_csFilter File selection filter mechanism, e.g. ".txt;.cpp;.h"
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetFileColumnDef( LONG in_lColumnIndex, const CString &in_csBrowseType = "File", const CString &in_csStartupPath = "/", const CString &in_csFilter = ".*" ) ;

	/*! Retrieves the siColumnFile definition for the given column.
	\param in_lColumnIndex The column of interest.
	\param out_csBrowseType "File" or "Folder" - determines the browser type to use when double-clicking.
	\param out_csStartupPath Startup directory for file or folder selection.
	\param out_csFilter File selection filter mechanism.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus GetFileColumnDef( LONG in_lColumnIndex, CString& out_csBrowseType, CString& out_csStartupPath, CString& out_csFilter ) const;

	/*! Changes a given column's type to siColumnShaderBall.
	\param in_lColumnIndex The column of interest.
	\param in_lThumbnailSize The thumbnail size to be used while drawing (from 28 to 128 pixels).
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetShaderBallColumnDef( LONG in_lColumnIndex, LONG in_lThumbnailSize = 28 ) ;

	/*! Retrieves the siColumnShaderBall definition for the given column.
	\param in_lColumnIndex The column of interest.
	\param out_lThumbnailSize The thumbnail size.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus GetShaderBallColumnDef( LONG in_lColumnIndex, LONG &out_lThumbnailSize ) const;

	/*! Changes a given column's type to siColumnImageClip.
	\param in_lColumnIndex The column of interest.
	\param in_lThumbnailSize The thumbnail size to be used while drawing (from 28 to 128 pixels).
	\since 12.0 (2014)
	*/
	CStatus SetImageClipColumnDef( LONG in_lColumnIndex, LONG in_lThumbnailSize = 28 );

	/*! Retrieves the siColumnImageClip definition for the given column.
	\param in_lColumnIndex The column of interest.
	\param out_lThumbnailSize The thumbnail size.
	\since 12.0 (2014)
	*/
	CStatus GetImageClipColumnDef( LONG in_lColumnIndex, LONG &out_lThumbnailSize ) const;

	/*! Inserts a new row.
	\param in_lRowIndex New row index. Passing -1 will insert a new row at the end of the table.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus InsertRow( LONG in_lRowIndex ) ;

	/*! Removes a row.
	\param in_lRowIndex Row to remove.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus RemoveRow( LONG in_lRowIndex ) ;

	/*! Inserts a new column. 
	\param in_lColumnIndex New column index. Passing -1 will insert a new row at the end of the table.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus InsertColumn( LONG in_lColumnIndex ) ;

	/*! Removes a column.
	\param in_lColumnIndex Column to remove.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus RemoveColumn( LONG in_lColumnIndex ) ;

	/*! Changes the background color of the cell.
	\param in_lCol Column of interest.
	\param in_lRow Row of interest.
	\param in_Color Background color to use.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetCellBackgroundColor( LONG in_lCol, LONG in_lRow, const CColor &in_Color ) ;

	/*! Retrieves the background color of the cell.
	\param in_lCol Column of interest.
	\param in_lRow Row of interest.
	\return Background color of the cell.
	\since 12.0 (2014)
	*/
	CColor GetCellBackgroundColor( LONG in_lCol, LONG in_lRow ) const ;

	/*! Changes the given columns visibility.
	\param in_alCols Array of column indices to change.
	\param in_bVisible New visibility value.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetColumnsVisibility( const CLongArray &in_alCols, bool in_bVisible ) ;

	/*! Changes the given rows visibility.
	\param in_alRows Array of row indices to change.
	\param in_bVisible New visibility value.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetRowsVisibility( const CLongArray &in_alRows, bool in_bVisible ) ;

	/*! Set the read-only flags for the given cells.
	\param in_alCells Array of cells. Column/row pairs representing the cells.
	\param in_bROFlag New read-only flag for the passed cell indices.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus SetCellReadOnlyFlags( const CLongArray &in_alCells, bool in_bROFlag ) ;

	/*! Retrieves the read-only flags for the given cells.
	\param in_alCells Array of cells. Column/row pairs representing the cells.
	\param in_bROFlag Array of booleans, representing the current read-only flags for the given cells.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus GetCellReadOnlyFlags( const CLongArray &in_alCells, CBitArray &out_aROFlags ) const;

	/*! Assigns the GridData multi selection mode.
	\param in_eSelectionMode The multi selection mode to use.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus PutMultiSelectionMode( XSI::siGridDataMultiSelectionMode in_eSelectionMode ) ;

	/*! Retrieves the GridData multi selection mode.
	\return The current multi selection mode.
	\since 12.0 (2014)
	*/
	XSI::siGridDataMultiSelectionMode GetMultiSelectionMode() const;

	/*! Sets the read-only mode for the whole grid data.
	\param in_bROFlag The read-only flag to use.
	\return Success or failure of operation.
	\since 12.0 (2014)
	*/
	CStatus PutReadOnly( bool in_bROFlag ) ;

	/*! Retrieves the current read-only mode for the whole grid data.
	\return The current read-only flag.
	\since 12.0 (2014)
	*/
	bool GetReadOnly() const;

	/*! Sets the sort type for the combo items associated with a column of type ::siColumnCombo. 
	If not set, use the default order of the combo items specified.
	\param in_ColumnIndex Column index (zero based)
	\param in_Type	Type of sort (None, sort by label, sort by value). See ::siGridWidgetColumnComboItemsSort for a complete
	list of possible control types.
	\return Success or failure of operation.
	\since 13.0 (2015)
	*/
	CStatus PutColumnComboItemsSortType(LONG in_ColumnIndex, siGridWidgetColumnComboItemsSort in_type);

	/*! Returns the sort type for the combo items associated with a column of type ::siColumnCombo.
	\param in_ColumnIndex Column index (zero based)
	\return Type of sort (None, sort by label, sort by value). See ::siGridWidgetColumnComboItemsSort for a complete
	list of possible control types.
	\since 13.0 (2015)
	*/
	siGridWidgetColumnComboItemsSort GetColumnComboItemsSortType(LONG in_ColumnIndex) const;

private:

	GridData * operator&() const;
	GridData * operator&();
};

};
#endif // __XSIGRIDDATA_H__
