/*	----------------------------------------------------------------------------------------------
	
	This callback registers the shader language parser, assigning it a ClassName in the call to 
	PluginRegistrar.RegisterShaderLanguageParser. Together with the shader definition's ClassName 
	and Major and Minor version information found in the Parse_Info callback, this sets up a 
	ProgID of "Puck.<shader_classname>.<major>.<minor>", such as "Puck.ColorShare.1.0".
*/
function XSILoadPlugin( in_reg )
{
	in_reg.Author = "SDK Documentation";
	in_reg.Name = "ShaderParserExample";
	in_reg.Major = 1;
	in_reg.Minor = 0;

	in_reg.RegisterShaderLanguageParser("Puck");
	return true;
}

/*	----------------------------------------------------------------------------------------------
	
	This callback fires immediately after XSILoadPlugin and tells Softimage to look in the 'puck' 
	folders under the user, workgroup, and factory locations for any .pck and .bck files to parse.
*/
function Puck_QueryParserSettings( in_ctxt )
{
	in_ctxt.SetAttribute("Folders", "puck");
	in_ctxt.SetAttribute("FileTypes", ".pck;.bck");		// two potential file types
	return true;
}

/*	----------------------------------------------------------------------------------------------
	
	This callback fires each time Softimage finds a file matching the criteria specified in the 
	Puck_QueryParserSettings callback. It is where you open and read the file to extract the
	shader definition's ClassName, Major and Minor versions, and then use that information to
	both build the ProgID and populate the preset manager for each shader definition found.
	
	NB:	When building a Shader Definition plug-in, we can decide on a Category and DisplayName 
		for each shader definition, but since this is a batch process, this example shows how 
		you can specify a more user-friendly DisplayName by inserting spaces before uppercase 
		letters in the ClassName, and dump the shader into one of two potential  sub-categories 
		depending on its filename's extension.
*/
function Puck_ParseInfo( in_ctxt )
{
	// Open file to get shader prog id + category for populating the preset manager
	var sFilename = in_ctxt.GetAttribute("Filename");
	var fso = new ActiveXObject("Scripting.FileSystemObject");
	var ts = fso.OpenTextFile(sFilename);
	
	// Fail and set an error if we couldn't open the file
	if (!ts) {
		in_ctxt.SetAttribute("Errors", "Couldn't open " + sFilename + " file\n" );
		return false;
	}

	// Comments are represented by a line starting with '#'
	// ShaderDef name is defined on a line starting with '=' followed by Major and then Minor values
	while (!ts.AtEndOfStream) {
		var sCurrLine = ts.ReadLine();
		if (sCurrLine.match(/^=/)) {
			// The only thing we care about is the name + version
			sCurrLine = sCurrLine.replace(/^=/, "");	// remove the '=' indicator
			var aTokens = sCurrLine.split(/ /g);		// chop it into meaningful chunks
			
			// Feed the PluginRegistrar
			var sClassID = aTokens[0];
			if (!sClassID) {
				in_ctxt.SetAttribute("Errors", "Couldn't find ClassName in " + sFilename + " file\n" );
				return false;
			}
			in_ctxt.SetAttribute("ClassName", sClassID);
			
			var lMajor = (typeof(aTokens[1]) != "undefined") ? aTokens[1] : 1;
			in_ctxt.SetAttribute("MajorVersion", lMajor);
			
			var lMinor = (typeof(aTokens[2]) != "undefined") ? aTokens[2] : 0;
			in_ctxt.SetAttribute("MinorVersion", lMinor);
			
			// Assign the main Category of "Test Shaders" and then put .pck files under "Parsed (Good)" 
			// subcategory followed by the .bck files under "Parsed (Bad)" subcategory
			if (in_ctxt.GetAttribute("Filename").match(/\.pck$/i)) {				// sub-categorize according to extension
				in_ctxt.SetAttribute("Category", "Example Shaders/Parsed/Good");	// order good sub-category before bad
			} else if (in_ctxt.GetAttribute("Filename").match(/\.bck$/i)) {
				in_ctxt.SetAttribute("Category", "Example Shaders/Parsed/Bad");
			} else {
				in_ctxt.SetAttribute("Category", "Example Shaders/Parsed");			// no categories come last (shouldn't happen)
			}
			
			// Make the DisplayName a more reader-friendly  version of the ClassName
			var sDisplayName = sClassID.replace(/_/g, " ");					// replace underscores with spaces
			sDisplayName = sDisplayName.replace(/([A-Z][a-z])/g, " $1");	// insert spaces before capitals
			sDisplayName = sDisplayName.replace(/^ /, "");					// remove leading spaces
			in_ctxt.SetAttribute("DisplayName", sDisplayName);
			
			// Quit parsing (that's all we need from this file for now
			break;
		}
	}
	
	return true;
}

/*	----------------------------------------------------------------------------------------------
	
	This callback fires when a shader is instantiated in Softimage. It is where the shader really 
	gets fleshed out: the parameters, renderer, attributes, etc. are defined on the ShaderDef object, 
	which is available from the Context object via the Definition attribute. 
*/
function Puck_Parse( in_ctxt )
{
	// Get shaderdef and open file to populate
	var oShaderDef = in_ctxt.GetAttribute("Definition");
	var sFilename = in_ctxt.GetAttribute("Filename");
	var fso = new ActiveXObject("Scripting.FileSystemObject");
	var ts = fso.OpenTextFile(sFilename);
	
	// Fail and set an error if we couldn't open the file
	if (!ts) {
		in_ctxt.SetAttribute("Errors", "Couldn't open " + sFilename + " file\n" );
		return false;
	}
	
	// Comments are represented by a line starting with '#'
	// ShaderDef name is defined on a line starting with '=' followed by Major and then Minor values
	// Parameters are defined on lines starting with '@' and following this syntax:
	// 		@[Name] [DataType]() [Direction=in|out] [Texturable=yes|no]
	// Shader library and its procedure and any attributes are represented like so:
	//		%[RendererName] [ProcedureCall] [CodePath] [Attrib1=Val1] [Attrib2=Val2] [...] [AttribN=ValN]
	var iLine = 0; 
	while (!ts.AtEndOfStream) {
		var sCurrLine = ts.ReadLine();
		iLine++;
		if (sCurrLine.match(/^#/)) {
			// Ignore it, it's a comment
		} else if (sCurrLine.match(/^=/)) {
			// Validate the class + version info against the ProgID and fail if it doesn't match
			sCurrLine = sCurrLine.replace(/^=/, "");	// remove the '=' indicator
			var sProgID = "Puck." + sCurrLine.replace(/ /g, ".");	// now it looks like a proper ProgID
			if (sProgID != oShaderDef.ProgID) {
				in_ctxt.SetAttribute("Errors", "Couldn't match definition in the " + sFilename 
					+ " file to the " + oShaderDef.ProgID + " ProgID at line " + iLine + "\n" );
				return false;
			}
			
			// If it's valid, add the texture family
			oShaderDef.AddShaderFamily("mrTexture");
		} else if (sCurrLine.match(/^@/)) {
			// It's a parameter definition, so let's go
			sCurrLine = sCurrLine.replace(/^@/, "");	// remove the '@' indicator
			var aTokens = sCurrLine.split(/ /g);		// chop it into meaningful chunks
			
			// Break the line into chunks
			if (aTokens.length < 4) {
				in_ctxt.SetAttribute("Warnings", "Couldn't get parameter info for " + oShaderDef.ProgID 
					+ " shader definition at line " + iLine + "\n" );
				continue;
			}
			
			// Get the direction so we know which ParamDefCollection to retrieve
			var oParamDefs;
			if (aTokens[2] == "in") {
				oParamDefs = oShaderDef.InputParamDefs;
			} else if (aTokens[2] == "out") {
				oParamDefs = oShaderDef.OutputParamDefs;
			} else {
				in_ctxt.SetAttribute("Warnings", "Couldn't find directionality of the parameter at line " 
					+ iLine + " for the " + oShaderDef.ProgID + " shader definition\n" );
				continue;
			}
			
			// Set whether it's texturable or not
			var oPDefOptions = XSIFactory.CreateShaderParamDefOptions();
			oPDefOptions.SetTexturable((aTokens[3] == "yes"));

			// Convert the string typename to the matching siShaderParameterDataType value
			var sRawType = aTokens[1].replace(/\(\)$/, "");
			var ePDType = FindParamDefType(sRawType);

			// See if this parameter is actually an array so we can call the right method
			if (ePDType != siShaderDataTypeUnknown) {
				if (aTokens[1].match(/\(\)$/)) {
					oParamDefs.AddArrayParamDef(aTokens[0], ePDType, oPDefOptions);
				} else {
					oParamDefs.AddParamDef(aTokens[0], ePDType, oPDefOptions);
				}
			}
		} else if (sCurrLine.match(/^%/)) {
			// Add renderer
			sCurrLine = sCurrLine.replace(/^%/, "");
			
			// Break the line into chunks
			var aTokens = sCurrLine.split(/ /);
			if (aTokens.length < 3) {
				in_ctxt.SetAttribute("Warnings", "Couldn't get renderer info for " + oShaderDef.ProgID 
					+ " shader definition at line " + iLine + "\n" );
				continue;
			}
			
			// Get the renderer name
			var sRendName = aTokens.shift();
			if (!sRendName) {
				in_ctxt.SetAttribute("Warnings", "Couldn't get renderer name for " + oShaderDef.ProgID 
					+ " shader definition at line " + iLine + "\n" );
				continue;
			}
			sRendName = sRendName.replace(/_/g, " ");
			
			// Get the procedure to call and the library path
			var oMetaRenderer = oShaderDef.AddRendererDef(sRendName);
			oMetaRenderer.SymbolName = aTokens.shift();
			oMetaRenderer.CodePath = aTokens.shift();
			
			// Set renderer options if found
			if (aTokens.length) {
				var oRendererOpts = oMetaRenderer.RendererOptions;
				while (aTokens.length) {
					var aPair = (aTokens.shift()).split("=");
					if (aPair.length != 2) { continue; }
					var sKey = aPair.shift();	
					if (!sKey) { break; }					// key must be valid
					var sVal = aPair.shift();
					oRendererOpts.Set(sKey, sVal);
				}
				
				// Report how many we found and what they were
				var aRendererOptNames = (new VBArray(oRendererOpts.Names)).toArray();
				if (aRendererOptNames) {
					Application.LogMessage("Found " + aRendererOptNames.length + " renderer option(s):\n\t" 
						+ aRendererOptNames.join("\n\t"));
				} else {
					in_ctxt.SetAttribute("Warnings", "Found no renderer options");
				}
			}
		} else {
			in_ctxt.SetAttribute("Warnings", "Can't parse line #" + iLine +": " + sCurrLine);
		}
	}
		
	return true;
}

// Convenience function to convert the name of a data type (eg., "integer" to 
// its siShaderParameterDataType equivalent (eg., siShaderDataTypeInteger). 
function FindParamDefType ( in_sType ) 
{
	switch (in_sType) {
		case "array" 		: return 	siShaderDataTypeArray;
		case "boolean" 		: return 	siShaderDataTypeBoolean;
		case "color3" 		: return 	siShaderDataTypeColor3;
		case "color4" 		: return 	siShaderDataTypeColor4;
		case "custom" 		: return 	siShaderDataTypeCustom;
		case "gradient" 	: return 	siShaderDataTypeGradient;
		case "image" 		: return 	siShaderDataTypeImage;
		case "integer" 		: return 	siShaderDataTypeInteger;
		case "matrix33" 	: return 	siShaderDataTypeMatrix33;
		case "matrix44" 	: return 	siShaderDataTypeMatrix44;
		case "fcurve" 		: return 	siShaderDataTypeProfileCurve;
		case "property" 	: return 	siShaderDataTypeProperty;
		case "quaternion" 	: return 	siShaderDataTypeQuaternion;
		case "reference" 	: return 	siShaderDataTypeReference;
		case "scalar" 		: return 	siShaderDataTypeScalar;
		case "string" 		: return 	siShaderDataTypeString;
		case "structure" 	: return 	siShaderDataTypeStructure;
		case "vector2" 		: return 	siShaderDataTypeVector2;
		case "vector3" 		: return 	siShaderDataTypeVector3;
		case "vector4" 		: return 	siShaderDataTypeVector4;
		default 			: return 	siShaderDataTypeUnknown;
	}
}
