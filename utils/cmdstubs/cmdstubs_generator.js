//*****************************************************************************
// cmdstubs.js
// Run this utility script to generate a C++ API function for each Softimage command.
//
// It is possible to include the output C++ code in your project and to use
// it to call any Softimage command as if it was a C++ function.  This saves some of the
// extra work of using Application::ExecuteCommand.  
//
// Any installed custom commands are also included in the generated output,
// so this can be useful for calling your own script-based commands from C++.
//*****************************************************************************

// globals
var cCRLF = String.fromCharCode( 13,10 );
var cTab = String.fromCharCode( 9 );

// This is the output location.  Normally it is the same path as the location of this
// script, but you can customize it.
var folder = XSIUtils.Environment("XSISDK_ROOT")+"/utils/cmdstubs";

var ObjectType=1;
var ObjectListType=2;
var StringType=3;
var BooleanType=4;
var ParameterListType=5;
var PresetType=6;
var NumberType=7;
var TimeType=8;
var EnumType=9;
var ValueType=10;

main();

function main()
{
	var fso = new ActiveXObject("Scripting.FileSystemObject");

	// collect unique entries
	var cmddict = new ActiveXObject("Scripting.Dictionary");
	var cmdfreqdict = new ActiveXObject("Scripting.Dictionary");
	
	var eCmds = new Enumerator( commands );
	for ( ; !eCmds.atEnd(); eCmds.moveNext() )
	{
		var item = eCmds.item();

		if ( ! cmddict.exists(item.scriptingname.toLowerCase()) )
		{
			cmddict.add( item.scriptingname.toLowerCase(), item);
			cmdfreqdict.add( item.scriptingname.toLowerCase(), 0 );
		}
		cmdfreqdict.item( item.scriptingname.toLowerCase() )++;
	}
	
	if ( fso.FolderExists( folder ) == false )
	{
		XSIUIToolkit.MsgBox( "The expected output directory " + folder + " does not exist.\nPlease update the script with the correct location.") ;
		return ;	
	}	
	
	// write out cmd doc
	cppfile = folder + "/cmdstubs.cpp";
	hfile = folder + "/cmdstubs.h";

	var oCppFile = fso.CreateTextFile( cppfile, true );
	var oHeaderFile = fso.CreateTextFile( hfile, true );
	
	// file header
	writefileheader( oCppFile );
	writefileheader( oHeaderFile );

	// includes
	oHeaderFile.writeline("#include <xsi_application.h>" );
	oHeaderFile.writeline("#include <xsi_value.h>" );
	oHeaderFile.writeline("#include <xsi_status.h>" );
	oHeaderFile.writeline("#include <xsi_string.h>" );

	oHeaderFile.writeline("");

	oHeaderFile.writeline("#ifndef EXPORTSTUBS" );
	oHeaderFile.writeline("#ifdef WIN32" );
	oHeaderFile.writeline("#define EXPORTSTUBS __declspec(dllexport)" );
	oHeaderFile.writeline("#else" );
	oHeaderFile.writeline("#define EXPORTSTUBS " );
	oHeaderFile.writeline("#endif" );
	oHeaderFile.writeline("#endif" );
	
	oHeaderFile.writeline("");

	oCppFile.writeline("#include \"cmdstubs.h\"" );
	oCppFile.writeline("");

	// namespace
	oCppFile.writeline("namespace XSI {" );
	oCppFile.writeline("namespace COMMANDS {" );
	oCppFile.writeline("");

	oHeaderFile.writeline("namespace XSI {" );
	oHeaderFile.writeline("namespace COMMANDS {" );
	oHeaderFile.writeline("");
	
	// global variables
	oCppFile.writeline("Application gApp;" );
	oCppFile.writeline("");

	// command function definitions	
	a = new VBArray( cmddict.keys() ).toArray();
	a.sort();
	for ( i in a )
	{
		key = a[i];
		cmd = cmddict.item(key);
		logmessage( cmd.scriptingname );	
		
		if ( cmd.scriptingname == "" )
		{
			logmessage( "Error: no script name " + cmd.name );
			continue;
		}		

		oCppFile.writeline("// " + cmd.scriptingname );
		if ( cmd.returnvalue )
		{
			str = ("CValue "+ cmd.scriptingname );
		} 
		else
		{	
			str = ("void " + cmd.scriptingname );
		}
			
		str += ("(");
		
		// dump the function signature
		re = / /g;
		for (var index=0, count=0; index < cmd.arguments.count; index++ )
		{
			var arg = cmd.arguments(index);

			try {	

				strPrefix = ArgFlagsToString(arg.flags);
				if (strPrefix == "unknown")
				{
					// some args aren't set flags e.g return value arg
					// just ignore them
					continue;
				}

				// some argument names contain spaces
				aname = arg.name.replace( re, "_");
				atype = VarTypeToCPPType( ArgTypeToVarType(arg), arg ); 
				avalue = arg.value; 
//		logmessage  ( "atype ->"+atype );
//		logmessage  ( "avalue ->"+avalue );
				if (count>0) 
				{
					str +=( "," );
				}	
				count++;

				str +=( " " + atype + " " + strPrefix + "_" + aname.toLowerCase());
			} catch (e) {
				// ignore private commands
				logmessage( e.description ); 
			}	
			
		}
		if ( count == 0 )
		{
			str +=(" void");
		}
		
		str +=(" )");
		oCppFile.writeline(str);

		oHeaderFile.writeline(cTab + "EXPORTSTUBS " + str + ";"); 
		oCppFile.writeline("{");

		oCppFile.writeline(cTab +"CValueArray args("+count+");");
		oCppFile.writeline(cTab +"CValue retval;");
		oCppFile.writeline("");

		// initialize array of arguments for ExecuteCommand
		for (var index=0; index < cmd.arguments.count; index++ )
		{
			var arg = cmd.arguments(index);

			try {	
				strPrefix = ArgFlagsToString(arg.flags);
				if (strPrefix == "unknown")
				{
					// some args aren't set flags e.g return value arg
					// just ignore them
					continue;
				}
			
				if (arg.flags == siArgumentOutput) 
				{
					// output args don't need to be initialized
					continue;
				}

				aname = arg.name.replace( re, "_");
				atype = ArgTypeToVarType(arg); 
				avalue = arg.value; 
				oCppFile.write( cTab +"args[" + index + "]= ");
				
				if ( atype == EnumType )
				{
					oCppFile.write( "(LONG)" );
				}

				oCppFile.writeline( strPrefix + "_" + aname.toLowerCase() + ";");
			} catch (e) { 
				aname="";
				// ignore private commands
			}
		}
		oCppFile.writeline("");

		oCppFile.writeline(cTab +"CStatus st = gApp.ExecuteCommand( L\""+cmd.ScriptingName+"\", args, retval );");
		oCppFile.writeline("");

		// set output arguments 
		for (var index=0; index < cmd.arguments.count; index++ )
		{
			var arg = cmd.arguments(index);

			try 
			{	
				strPrefix = ArgFlagsToString(arg.flags);
				if (strPrefix == "unknown")
				{
					// some args aren't set flags e.g return value arg
					// just ignore them
					continue;
				}
			
				aname = arg.name.replace( re, "_");
				atype = ArgTypeToVarType(arg); 

				if (arg.flags != siArgumentInput) 
				{
					// ignore input args
					strOutArg = strPrefix + "_" + aname.toLowerCase();
					
					oCppFile.write( cTab + strOutArg + " = ");
					if ( atype == EnumType )
					{
						atype = VarTypeToCPPType( ArgTypeToVarType(arg), arg ); 
						oCppFile.write( "("+atype+")(LONG)" );
					}
					oCppFile.writeline( "args[" +index+ "];" );					
				}
			} 
			catch (e) 
			{ 				
				oCppFile.writeline( "something wrong" );
			}	
		}
		
		if ( cmd.returnvalue )
		{
			oCppFile.writeline(cTab +"return retval;");
		}		
		else
		{
			oCppFile.writeline(cTab +"return;");
		}		

		oCppFile.writeline("}");
		oCppFile.writeline("");
	}
	
	// close namespace scope
	oCppFile.writeline("};");
	oCppFile.writeline("};");
	oHeaderFile.writeline("};");
	oHeaderFile.writeline("};");

	oCppFile.close();
}

function PrintCmdInfo( name )
{
	var cmd = Application.Commands(name);
		
	if ( cmd != "null" ) {
		str = cmd.name + " command"  + cCRLF;
		str +=	cTab + "category: "		+ cmd.category  + cCRLF;  
		str += cTab + "description: "	+ cmd.description  + cCRLF;
		str += cTab + "tooltip: "		+ cmd.tooltip  + cCRLF;
		str += cTab + "scriptingname: " + cmd.scriptingname  + cCRLF;
		str += cTab + "handler: " 		+ cmd.handler	 + cCRLF;
		str += cTab + "filename: " 	+ cmd.filename  + cCRLF;
		str += cTab + "language: " 	+ cmd.language  + cCRLF;
		str += cTab + "builtin: " 		+ cmd.builtin  + cCRLF;
		str += cTab + "returnvalue: " + cmd.returnvalue  + cCRLF;
	
		str += cTab + "Arguments:" + cCRLF;
		
		for (index=0; index < cmd.arguments.count; index++ )
		{
			var arg = cmd.arguments(index);

			try {	arg.value; }
			catch (e)	{ arg=null; }	
				
			if ( arg == null )
			{	
				str += cTab + cTab + "Arg" + index + " private" + cCRLF;
			}
			else 
			{	
				str += cTab + cTab + "Arg" + index + " ";
				str += "name=" + arg.Name 	+ ", ";
				str += "flags=" + ArgFlagsToString(arg.Flags) 	+ ", ";
				str += "value=" + arg.Value 	+ cCRLF; 
			}
		}
		logmessage( str );
	} else {
		logmessage( name + cTab + "command is not installed" );
	}
}

function ArgFlagsToString(flags)
{
	switch ( flags )
	{
		case siArgumentInput : return "in";
		case siArgumentOutput : return "out";
		case siArgumentInputOutput : return "io";
		default : return "unknown";
	}	
}

function VarTypeToCPPType( vtype, a )
{	
	strConst = "";
	if (a.flags == siArgumentInput )
	{
		strConst = "const";
	}
	
	switch ( vtype ) 
	{ 
		case ObjectListType:
		{
// C++ API doesn't support converting CRefArray to CValue
			return strConst + " CValueArray& /*objects*/";
		}
		
		// selected component
		case ObjectType:
		{
			return strConst + " CValue& /*object*/";
		}	
		// animated (or marked) parameters
		case ParameterListType:
		{
// C++ API doesn't support converting CRefArray to CValue
			return strConst + " CValueArray& /*anim params*/";
		}	
		// current frame 
		case TimeType:
		{
			return strConst + " CTime& /*frame*/";
		}
		// preset 
		case PresetType:
		{
			return strConst + " CString& /*preset*/";
		}
		// enum 
		case EnumType:
		{
			var aStr = a.value.split(":");
			if (aStr[0]=="")
			{
				// format: :siEnumValue:siEnumType
				return aStr[2];
			}
			// foormat: siEnumValue:siEnumType
			return aStr[1];
		}
		case StringType:
		{
			return strConst + " CString&";
		}
		case NumberType:
		{
			return strConst + " CValue& /*number*/"
		}	
		case BooleanType:
		{
			return "bool";
		}	
		default: 
		{
			return strConst + " CValue& ";
		}	
	};
}


function ArgTypeToVarType( a )
{
	atype = typeof(a.value)
	
   	if ( atype == "string" ) 
	{
		// These are the command handler GUIDs
		reObjs = /7834CB8C/g;
		reObj = /55F36231/g;
		reAnimParams = /FA0B5D32/g;
		rePreset = /42FC2493/g;
		reFrame = /7835DE3259C4CB8C/g;
		reEnum = /:si/g;
		
		// selected objects
		if ( a.value.search(reObjs ) != -1 ) {
			return ObjectListType;
		}
		// selected component
		else if ( a.value.search(reObj) != -1 )
		{
			return ObjectType;
		}	
		// animated (or marked) parameters
		else if ( a.value.search(reAnimParams) != -1)
		{
			return ParameterListType;
		}	
		// current frame 
		else if ( a.value.search(reFrame)!= -1 )
		{
			return TimeType;
		}
		// preset 
		else if ( a.value.search(rePreset) != -1)
		{
			return PresetType;
		}
		// enum 
		else if ( a.value.search(reEnum) != -1)
		{
			return EnumType;
		}
		return StringType;
	}	
	else if ( atype == "object" )
	{
		return ObjectType;
	}
	else if (atype == "number" )
	{
// cannot tell if value if Double or Long	
			return NumberType;
	}	
	else if (atype == "boolean" )
	{
		return BooleanType;
	}	
	else
	{
		return ValueType;
	}	
}

function writefileheader(oCppFile)
{
	oCppFile.writeline("// command function stubs" );
	oCppFile.writeline("// Softimage v"+Application.Version() );
	oCppFile.writeline("");
}

function PrintArgument( arg )
{
	logmessage( cTab + arg.name +":"+ arg.flags );
}

function FindCmdByScriptName( scriptingname )
{
	var eCmds = new Enumerator( commands );

	var cmd = null;

	for ( ; !eCmds.atEnd(); eCmds.moveNext() )
	{
		var item = eCmds.item();
		
		if ( item.scriptingname.toLowerCase() == scriptingname.toLowerCase() )
		{
			logmessage( item.name );
			cmd = eCmds.item();
			break;
		}
	}
	return cmd;
}
