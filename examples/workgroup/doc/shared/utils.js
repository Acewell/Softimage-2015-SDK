var isIE5 = (navigator.appVersion.indexOf("MSIE 5")>0) || (navigator.appVersion.indexOf("MSIE")>0 && parseInt(navigator.appVersion) >= 4);
var bIsLinuxOS = false;
var bIsNetView = false;
var bIs64Bit = null;		// null means we don't know (eg we are in a browser); in NetView, this flag is true or false
var bIsChm = false;

var g_xsiapp  = null;
var g_app = null;
var g_xsiutils = null;
var g_xsifactory = null;

var g_dbg;
var g_slash;


window.onload = onLoadHandler;

function onLoadHandler() {
	isChm();
	isNetView();
	isLinux();
	is64Bit();
	
	g_slash = getSlash();

	if (isIE5 && !isLinux() && false) { 
		var l_fso = new ActiveXObject("Scripting.FileSystemObject");
		g_dbg = l_fso.CreateTextFile("C:\\utils.debug");
	}

	updatePage();
}


function getSlash()
{
	var sSlash  = '';
	
	if ( bIsNetView ) {
		sSlash = g_xsiutils.Slash;
	} else if ( bIsLinuxOS ) {
		sSlash = '/';
	} else {
		sSlash = '\\';
	}
	
	return sSlash;
}


//-------------------------------------------
// Set the global flag that indicates
// whether the page is in a .chm
//-------------------------------------------
function isChm()
{
	if ( location.pathname.match(/\.chm/i) ) { bIsChm = true; }
}

//-------------------------------------------
// Create instances of Softimage objects.
// Set the global bIsNetView flag.
//-------------------------------------------

function isNetView()
{
	try {
		g_xsiapp = new ActiveXObject('XSI.Application');
		g_app = g_xsiapp.Application;
		g_xsiutils = new ActiveXObject('XSI.Utils');
		g_xsifactory = new ActiveXObject('XSI.Factory');
		bIsNetView = !(g_xsiapp == null || g_app  == null || g_xsiutils  == null || g_xsifactory == null);
	} catch ( e ) {
		bIsNetView = false;
	}

	// Forget about what you know if you're really in CHM
	if ( bIsChm ) { bIsNetView = false; }
}


//-------------------------------------------
// Set the global bIsLinuxOS flag
//-------------------------------------------
function isLinux()
{
	if ( !bIsNetView ) {
		// detect the OS
		var sUserAgent = navigator.userAgent.toLowerCase();
		bIsLinuxOS = ( sUserAgent.indexOf('linux') != -1 );
	} else {
		// detect the OS
		bIsLinuxOS = g_xsiutils.IsLinuxOS();
	}
}


//--------------------------------------------
// Set the global bIs64Bit flag
//--------------------------------------------
function is64Bit()
{
	if ( bIsNetView ) {
		bIs64Bit = g_xsiutils.Is64BitOS();
	}
}


//--------------------------------------------
// Get the current version of Softimage from 
// the install path
//--------------------------------------------
function getCurrentXSIVersion()
{
	var sRawVer, sVersion = "";
	var sXSIHome = location.pathname;
	if ( sXSIHome.match(/Softimage( |_)(.+)$/i) ) {
		sRawVer = RegExp.$2;
	} else {
		return "";
	}

	if ( sRawVer.match(/^([0-9]{4})/) ) {
		return RegExp.$1;
	} else {
		return "";
	}
}


//-------------------------------------------
// Get the install path for the example
//
// The HTML page is installed with the example
// so we use location.pathname.
//-------------------------------------------
function getInstallPath()
{
	if ( this.sInstallPath != undefined ) { return this.sInstallPath; }
	
	var l_slash = getSlash();
	if ( bIsChm ) {
		this.sInstallPath = '$XSISDK_ROOT' + l_slash + 'examples' + l_slash + 'workgroup' 
			+ l_slash + 'Addons' + l_slash + document.title + getSlash();
	} else {
		var x = location.pathname.lastIndexOf(l_slash);
		// Linux: pathname = /var/tmp/XSI_XX/XSISDK/examples/workgroup/examples/MyExample
		this.sInstallPath = location.pathname.substring( (bIsLinuxOS ? 0 : 1), x+1 );
	}
	
	return this.sInstallPath;
}

//-------------------------------------------
// Get the workgroup path for the example
//-------------------------------------------
function getWorkgroupPath()
{
	if ( this.workgroupPath != undefined ) { return this.workgroupPath; }
	
	var l_slash = getSlash();
	if ( bIsChm ) {
		this.sInstallPath = '$XSISDK_ROOT' + l_slash + 'examples' + l_slash + 'workgroup';
	} else {
		var y = location.pathname.lastIndexOf(l_slash + 'workgroup');
		this.workgroupPath = location.pathname.substring( 1, y+10 );
	}
	
	return this.workgroupPath;
}


// Currently a grab bag of stuff related to updating the page based on the context 
// (are we in Softimage or just in a browser) and inserting html (eg A elements with onclick handlers)
function updatePage() {
	if ( !bIsNetView && isIE5 ) {
		// Show the install step if we're not in a NetView page
		var oInstallStep = document.getElementById( "toinstall" );
		if ( oInstallStep ) { oInstallStep.style.display = "block" };
	}
	
	// Hide OS-specific build instructions
	var oDiv = ( bIsLinuxOS ) ? document.getElementById( "windows-build" ) : document.getElementById( "linux-build" );
//	if ( oDiv ) { oDiv.style.display = "none"; }

	// Show/hide the section about viewing CHM files on Linux
	var oChm = document.getElementById( "linux-chm" );
	if ( oChm ) { oChm.style.display = ( bIsLinuxOS ) ? 'block' : 'none'; }

	// Show/hide the keywords section (keywords are visible only in .chm)
	var oKeywords = document.getElementById( "keywords" );
	if ( oKeywords ) { oKeywords.style.display = ( bIsChm ) ? 'block' : 'none'; }

	var oFirstImage = document.images[0];
	if ( oFirstImage ) { oFirstImage.style.display = ( bIsChm ) ? 'none' : 'block' ; }

	//--------------------------------------------------
	// Replace <span> elements 
	//--------------------------------------------------

	var installPath = getInstallPath();
	var workgroupPath = getWorkgroupPath();
	var xsiVersion = getCurrentXSIVersion();
	var oSpans = document.getElementsByTagName( "span" );

	for (var i=0; i < oSpans.length; i++ ) {
		var span = oSpans[i];
		if (g_dbg) { g_dbg.WriteLine("\nCURRENT SPAN: " + span.toString()); }
		if ( span.className == "installPath" ) {
			if (g_dbg) { g_dbg.WriteLine("\t is installPath"); }
			// FIREFOX: use innerHTML instead of innerText
			//o.innerText = installPath;
			var sTmp = span.innerHTML;
			if ( sTmp.indexOf('vcproj') != -1 ) {
				sTmp = getVcProj( sTmp );
				if ( sTmp.indexOf('\\') == -1 ) {
					sTmp = 'cppsrc' + getSlash() + sTmp;
				}
			}
			if ( sTmp.indexOf('csproj') != -1 ) {
				sTmp = getVcProj( sTmp );
				if ( sTmp.indexOf('\\') == -1 ) {
					sTmp = 'cssrc' + getSlash() + sTmp;
				}
			}
			span.innerHTML = installPath + sTmp;
		} else if ( span.className == "workgroupPath" ) {
			if (g_dbg) { g_dbg.WriteLine("\t is workgroupPath"); }
			span.innerHTML = workgroupPath
		} else if ( span.className == 'envVar' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is envVar"); }
			span.innerHTML = ( bIsLinuxOS ) ? '$'+span.innerHTML : '%'+span.innerHTML+'%';
		} else if ( span.className == 'linuxExt' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is linuxEnv"); }
			if (xsiVersion) { span.innerHTML = ".xsi_" + xsiVersion; }
		} else if ( bIsNetView && !bIsLinuxOS && span.className == 'sishell' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is sishell"); }
			var sCSrcFolder = span.cppsrc;
			// Trap in case this is for a C# source file
			if ( !sCSrcFolder ) { sCSrcFolder = span.cssrc; }
			// By default shells will try to open in cppsrc file location, so if this is for C#, devs should use the .cssrc attribute
			sCSrcFolder = ( sCSrcFolder == '' || sCSrcFolder == null || sCSrcFolder == "undefined") ? "cppsrc" : sCSrcFolder;
			if (g_dbg) { g_dbg.WriteLine("\t\t sCSrcFolder = "+sCSrcFolder); }
			if ( sCSrcFolder.indexOf('INSTALL_FOLDER') != -1 ) { sCSrcFolder = ''; }
			if (g_dbg) { g_dbg.WriteLine("\t\t innerHTML = "+'<a href="SIShell.bat" onclick="openCommandPrompt(\'' + sCSrcFolder + '\');return false;" title="Click here to open a Softimage command prompt">' + span.innerText + '</a>'); }
			span.innerHTML = '<a href="SIShell.bat" onclick="openCommandPrompt(\'' + sCSrcFolder + '\');return false;" title="Click here to open a Softimage command prompt">' + span.innerText + '</a>';
		} else if ( bIsNetView  && !bIsLinuxOS && span.className == 'devenv' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is devenv"); }
			var sProj = span.vcproj;
			// Trap in case this is a C# project file
			if ( !sProj ) { sProj = span.csproj; }

			// If sProj doesn't include any slashes, then
			// it doesn't include a folder, so we assume the
			// project is in the cppsrc/cssrc folder
			sProj = sProj.replace(/\//g, '\\');
			if ( sProj.indexOf('\\') == -1 ) { sProj = 'cppsrc' + g_xsiutils.Slash + sProj; }

			// getVcProj figures out whether we want .vcproj or .64.vcproj
			var sProj = getVcProj( sProj );

			// Escape the slashes
			sProj = sProj.replace(/\\/g,'\\\\');
			if (g_dbg) { g_dbg.WriteLine("\t\t sProj = "+sProj); }
			
			if (g_dbg) { g_dbg.WriteLine("\t\t innerHTML = "+'<a href="' + sProj + '" onclick="loadProject(\'' + sProj + '\');return false;" title="Click to load the project into Visual C++">' + span.innerText + '</a>'); }
			span.innerHTML = '<a href="' + sProj + '" onclick="loadProject(\'' + sProj + '\');return false;" title="Click to load the project into Visual C++">' + span.innerText + '</a>';

		} else if ( bIsNetView && span.className == 'runCmd' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is runCmd"); }
			var sCmd = span.innerText;
			var sTitle = ( span.title ) ? span.title : "Click here to run the command " + sCmd;
			span.innerHTML = '<a href="' + sCmd + '" onclick="runCommand(\'' + sCmd + '\');return false;" title="' + sTitle +  '">' + sCmd + '</a>';
		} else if ( bIsNetView && span.className == 'runCommand' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is runCommand"); }
			var sTitle = ( span.title ) ? span.title : "Click here to run the command " + span.id;
			span.innerHTML = '<a href="#" onclick="runCommand(\'' + span.id + '\');return false;" title="' + sTitle + '">' + span.innerText + '</a>';
		} else if ( bIsNetView && span.className == 'runExample' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is runExample"); }
			var sTitle = ( span.title ) ? span.title : "Click here to run the example";
			span.innerHTML = '<a href="#" onclick="runExample(\'' + span.id + '\');return false;" title="' + sTitle + '">' + span.innerText + '</a>';
		} else if ( bIsNetView && span.className == 'loadScript' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is loadScript"); }
			var sTitle = ( span.title ) ? span.title : "Click here to load this code into a script editor";
			span.innerHTML = '<a href="#" onclick="loadScript(this.parentNode);return false;" title="' + sTitle + '">' + span.innerText + '</a>';
		} else if ( bIsNetView && span.className == 'getHelp' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is getHelp"); }
			var sTitle = ( span.title ) ? span.title : "Click here to open a help topic";
			span.innerHTML = '<a href="#" onclick="getHelp(\'' + span.id + ' \');return false;" title="' + sTitle + '">' + span.innerText + '</a>';
		} else if ( bIsNetView && span.className == 'showFile1' ) {
			if (g_dbg) { g_dbg.WriteLine("\t is showFile1"); }
			var sTitle = ( span.title ) ? span.title : "Click here to open the source file";
			var sFile = ( bIsLinuxOS ) ? span.file.replace(/\\/g, '/' ) : span.file.replace(/\\/g, '\\\\' );
			span.innerHTML = '<a href="#" onclick="showFile1(\'' + sFile + '\',' + '\'' + span.id + '\');return false;" title="' + sTitle + '">' + span.innerText + '</a>';
		}
	}	


	// Gussy up the list of example files.
	// - Add an image based on the file type.
	// - Add a link to the file that opens it for editing
	//   .vcproj and .csproj files are a special case; if marked up properly in the  
	//    html file, there will already be a link that opens the project in VC++
	var files = document.getElementsByTagName( "div" );
	for ( var i=0; i < files.length-1; i++ ) {
		if (g_dbg) { g_dbg.WriteLine("\nCURRENT DIV: " + files[i].toString()); }
		if ( files[i].className == 'examplefile') {
			if (g_dbg) { g_dbg.WriteLine("\tis examplefile"); }
			var oFile = files[i];
			var sFilename = (oFile.childNodes[0].nodeValue) ? oFile.childNodes[0].nodeValue : oFile.innerText;
			if (g_dbg) { g_dbg.WriteLine("\tFilename: "+sFilename); }
			var x = sFilename.lastIndexOf('.');
			if (g_dbg) { g_dbg.WriteLine("\tStart of extension: "+x); }
			var sFileType = ( x == -1 && sFilename.indexOf('GNU') > -1 ) ? 'mak' : sFilename.substring( x+1, sFilename.length );
			if (g_dbg) { g_dbg.WriteLine("\tfile type = " + sFileType); }

			// Hide OS-specific files (GNUmakefiles and .vcproj files)
			switch( sFileType ) {
				case 'mak':
					if ( !bIsLinuxOS ) { oFile.style.display = 'none'; }
					break;
				case 'csproj':
				case 'vcproj':
					if ( bIsLinuxOS ) {
						oFile.style.display = 'none';
					} else {
						// .vcproj OR .64.vcproj?
						var sTmp = oFile.innerHTML;
						sTmp = getVcProj( sTmp );
						oFile.innerHTML = sTmp;
						sFilename = sTmp;						
					}
					break;
			}
			var sImg = '<img src="..\\..\\doc\\shared\\' + sFileType + 'File.png" style="position:relative;bottom:-3px;">';

			sAstart = '';
			sAend = '';
			if ( bIsNetView ) {
				var sFolder = oFile.getAttribute( 'folder', 0 );
				if (g_dbg) { g_dbg.WriteLine("\tfolder = " + sFolder); }
				if ( !sFolder ) {
					if (g_dbg) { g_dbg.WriteLine("\t(thinks folder is null/undef)"); }
					switch( sFileType ) {
						case 'cpp':
						case 'h':
						case 'mak':
						case 'vcproj':
							sFolder = 'cppsrc' + g_xsiutils.Slash;
							break;
						case 'cs':
						case 'csproj':
							sFolder = 'cssrc' + g_xsiutils.Slash;
							break;
						case 'spdl':
							sFolder = 'Application' + g_xsiutils.Slash + 'spdl' + g_xsiutils.Slash;
							break;
						case 'xsivw':
							sFolder = 'Application' + g_xsiutils.Slash + 'views' + g_xsiutils.Slash;
							break;
						default:
							sFolder = 'Application' + g_xsiutils.Slash + 'Plugins' + g_xsiutils.Slash;
					}
				} else {
					sFolder = sFolder + '\\';
				}

				sAstart = '<a href="' + sFolder + sFilename + '" onclick="showFile(this.href); return false;" title="Click to open the file in a script editor">';
				sAend = '</a>';

				if ( sFileType == 'vcproj' ) {
					var sTmp = ( sFolder == null || sFolder == "undefined" ) ? 'cppsrc' : sFolder;
					sTmp += '\\' + sFilename;
					sTmp = sTmp.replace(/\\/g, '\\\\' );
					sAstart = '<a href="' + sFilename + '" onclick="loadProject(\'' + sTmp + '\');return false;" title="Click to load the project into Visual Studio .Net">';
				} else if ( sFileType == 'csproj' ) {
					var sTmp = ( sFolder == null || sFolder == "undefined" ) ? 'cssrc' : sFolder;
					sTmp += '\\' + sFilename;
					sTmp = sTmp.replace(/\\/g, '\\\\' );
					sAstart = '<a href="' + sFilename + '" onclick="loadProject(\'' + sTmp + '\');return false;" title="Click to load the project into Visual Studio .Net">';
				}
				
				// Log it
				if (g_dbg) { g_dbg.WriteLine("\t sTmp = " + sTmp); }
			}

			files[i].innerHTML = sImg + " " + sAstart +  oFile.innerHTML + sAend;
			if (g_dbg) { g_dbg.WriteLine("\t innerHTML = " + sImg + " " + sAstart +  oFile.innerHTML + sAend); }

		} // end if examplefiles
	} // end for loop
	
	
	// If we are in Softimage, change the flat list of views into 
	// a list of links that actually open the views
	if ( bIsNetView ) {
		var LIs = document.getElementsByName( 'view' );
		if ( LIs.length > 0 ) {
			var e = new Enumerator( LIs );
			for ( ; !e.atEnd(); e.moveNext() ) {
				var LI = e.item();
				var sFilename = LI.getAttribute( 'file', 0 );

				// innerText for a LI comes back with an extra space at the end
				var sViewName = trim( LI.innerText );
				var sAstart = '<a href="' + sFilename + '" onclick="openView(\'' + sViewName + '\'); return false;">';
				var sAend = '</a>';
				LI.innerHTML = sAstart +  LI.innerText + sAend;
			}
		}
	}

	return;
}

function trim (s) 
{  
	return s.replace(/^\s+|\s+$/g, '');  
}  



function openView( sFile )
{
	var r = g_app.OpenView( sFile );
}


function showFile( sFile )
{
	sFile = (bIsLinuxOS) ? sFile.replace( "file://", "" ) : sFile.replace( "file:///", "" );

	var r = g_app.ShowFileForEdit( sFile );
}


function showFile1( sFile, sEntryPoint )
{
	var sTmp = g_xsiutils.BuildPath( 
			getInstallPath(),
			sFile
			);


	var oView = g_app.ShowFileForEdit( sTmp );

	// if the file is already loaded into a script editor,
	// ShowFileForEdit returns null
	if ( oView != null ) {
		oView.SetAttributeValue( "entrypoint", sEntryPoint );
	} else {
		var oViews = g_app.Desktop.ActiveLayout.Views;
		for (var i=0; i<oViews.count; i++) {
			var v = oViews(i);
			if ( v.Type == "Text Editor" ) {
				if ( v.GetAttributeValue("filename") == sFile );
				v.SetAttributeValue( "entrypoint", sEntryPoint );
			}
		}

	}

}

//-------------------------------------------
//  Display a help topic from xsisdk.chm
//-------------------------------------------
function getHelp( sTopic )
{ 
	try {
		var sURL = g_xsiutils.BuildHtmlHelpURL( sTopic );
		g_xsiutils.DisplayHtmlHelp( sURL );
	}
	catch ( e ) {
		if ( g_app ) {
			g_app.LogMessage( "Cannot find the requested help topic." );
		} else {
			alert( "Cannot find the requested help topic." );
		}
	}
}


function showCHM( sChmFile )
{ 
		g_xsiutils.DisplayHtmlHelp( sChmFile );
}

function runCommand( sCmd )
{
	var oCmd = g_app.Commands( sCmd );

	if ( oCmd != null )
	{
		oCmd.Execute();
	}
	else
	{
		g_app.LogMessage( "Cannot find the command " + sCmd );
	}
}


//-------------------------------------------------------------------------
// NOTE
// To open an Softimage command prompt, we generate a temporary .js file
// and run it with wscript.exe.
//
// If you use XSIUtils.LaunchProcess (or the System command) to open an Softimage
// command prompt, it inherits the environment from Softimage.
//
// Softimage changes the TMP and TEMP environment variables
// (eg to something like %TMP%\XSI_TEMP_2744).
//
// devenv uses the temp folder for compiler intermediate files. 
// 
// As long as Softimage is still running, you can build the example. But if 
// you exit Softimage and keep devenv running, the next time you try to build 
// the example you'll get errors like this:
//
//	c1xx : fatal error C1083: Cannot open compiler intermediate file: 
//	'C:\DOCUME~1\sblair\LOCALS~1\Temp\XSI_Temp_2116\_CL_aaa04008ex': 
//	No such file or directory
//
//-------------------------------------------------------------------------


function openCommandPrompt( in_sCSrcFolder )
{
	var sCmd = g_xsiutils.BuildPath(
			g_app.InstallationPath( 3 ),
			"Application",
			"bin",
			"SIShell.bat"
			);

	var sCmd = sCmd.replace(/\\/g, '\\\\' );

	launchProcess( sCmd, in_sCSrcFolder );

}

//----------------------------------------------------------
// This function is called on Windows, from NetView.
// So we can test bIs64Bit without worrying about whether
// we are on Linux or Windows.
//----------------------------------------------------------
function loadProject( sProject )
{
	var sFullPath = g_xsiutils.BuildPath(
			getInstallPath(),
			sProject
			);

	var sCmd = "devenv " + sFullPath;
	
	var x = sProject.split('\\')
	var sCSrcFolder = (x.length == 2) ? x[0] : '';

	sCmd = sCmd.replace(/\\/g, '\\\\' );

	launchProcess( sCmd, sCSrcFolder );
	
}


//--------------------------------------------------------------------------
// 
// Sets the TMP user environment variable before launching a process.
// Softimage appends a temp folder (for example, XSI_TEMP_3344) to the TMP env var,
// We have to remove this temp folder from TMP before launching a process
// like devenv, or SIShell.bat (because a user can start devenv from SIShell.bat).
//
//--------------------------------------------------------------------------
function launchProcess( sCmd, in_sCSrcFolder )
{
	// Use XSIFactory.CreateActiveXObject instead of 'new ActiveXObject' to 
	// avoid IE security warnings about unsafe ActiveX controls.
	var oFSO = g_xsifactory.CreateActiveXObject("Scripting.FileSystemObject");

	// Get the temp folder. This will be the Softimage temp folder eg %USERPROFILE%/temp/XSI_TEMP_2233
	var TemporaryFolder = 2;
	var oTmpFolder = oFSO.GetSpecialFolder(TemporaryFolder);
	
	// Generate a random name for our .js file
	var sTmpFilename = oFSO.GetTempName();


	
	// Write the required script to the file
	var oFile = oTmpFolder.CreateTextFile( sTmpFilename + ".js" );

	oFile.WriteLine("var Shell = WScript.CreateObject(\"WScript.Shell\");" );
	oFile.WriteLine("var sTmp = Shell.ExpandEnvironmentStrings(\"%TMP%\");" );
	oFile.WriteLine("var i = sTmp.lastIndexOf(\"XSI_Temp_\");" );
	oFile.WriteLine("sTmp = sTmp.substring(0,i-1);" );
	oFile.WriteLine("var WshEnv = Shell.Environment(\"PROCESS\");" );
	oFile.WriteLine("WshEnv(\"TMP\") = sTmp;" );
	oFile.WriteLine("try {" );
	oFile.WriteLine("Shell.Run( \"" + sCmd + "\", 1, true );");
	oFile.WriteLine("} catch(e) {" );
	if ( sCmd.indexOf( "devenv" ) != -1 ) {
		oFile.WriteLine("Shell.Popup(\"Cannot run devenv.exe. Check that devenv.exe is in your path.\");");
	} else {
		oFile.WriteLine("Shell.Popup(\"Cannot run the command " + sCmd + "\");" );
	}
	oFile.WriteLine("}");
	oFile.Close();


	var sStartInPath = getInstallPath();
	if ( sStartInPath.match(/(\\|\/)$/) == null ) { sStartInPath += g_xsiutils.Slash; }
	sStartInPath += in_sCSrcFolder;
	try {
		g_xsiutils.LaunchProcess( "wscript " + oTmpFolder.Path + g_xsiutils.Slash + sTmpFilename + ".js", false, sStartInPath );
	}
	catch ( e ) {
		if ( g_app ) {
			g_app.LogMessage( "Cannot launch the process." );
		} else {
			alert( "Cannot launch the process." );
		}
	}
	
}


// This function works with this markup:
//
// <p>Hey, click <a href="#" onclick="loadScript(this);return false;">here</a>/</p>
// <pre>Demo script</pre>
//
// TODO: Look forward for the next PRE.
//
function loadScript( o )
{
	if ( o.parentNode.nextSibling.nodeName == 'PRE' )
	{
		var sJsDemoScript = o.parentNode.nextSibling.childNodes(0).nodeValue;

		var oActiveLayout = g_app.Desktop.ActiveLayout;
		var oScriptEditor = oActiveLayout.CreateView( "script editor", "DemoScript" );
		oScriptEditor.SetAttributeValue( "text", sJsDemoScript );
	}

}



//-------------------------------------------
// Get the file extension for the project
//-------------------------------------------
function getVcProj( s )
{
	return s;
}
