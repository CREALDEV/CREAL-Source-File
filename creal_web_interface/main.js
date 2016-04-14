var internalNodeConnection =[];	//this I guess makes the element an array
var actionStringTable = ["nonaction","Increase","Decrease","Change","Maintain","Transport","nonaction"]; 
var conditionStringTable = ["nonrelation", "=", ">", "<", ">=","<=","!="]; 

var internalNodeCounter = 0;	//this is a counter for the node being used at the time 
var appName = "Creal Alpha"; 
var appVers = "Build Version .733" 
var selectedMenuType = null;
var selectedSubType = null;
var selectedNode = null;
var selectedProperty = null;
var selectedAction = null;
var selectedCondition = null;

var mainJsonFile = null;	//this is the main json file right here
var currentDemoJson = null; 
var selectedLeftPaneNode = null;	//this is important right here in ordre to get the left pane shit going on 

var rightFrame = null;
var debugVar = true;		//this is the main debug variable right here 
var demoVar = false; //changed this to false, if its true it will run things as a demo..

var middleFrameGlobalState = null;

var selected = null;		// I don't know what i am doing right here 
var isVoid = null;		// I don't know what i am doing right here 
var selectedNill = null;	// I don't know what i am doing right here 

var visualOrSimState = null;
var internalNodeActionCounter = 0;	//this is a counter for actions 
var internalNodePropertiesCounter = 0;	//this is a counter for the properties within the nodes

var applicationName = "CreaCloud";	//this is the main app name right here 

var initialNode = null;
var nodeCount, actionListCount, propertyCount;
nodeCount = actionListCount = propertyCount = 1;
var globalX, globalY, globalSvgX, globalSvgY;	//these are the X and Y variables used to set objects on the screen. 

//new d3 stuff 
var graph =	{"nodes":[],"links":[]};

//~ var width = 640, height = 480;
 

var targetList=[]; //this is a global target list for the simulation 
var targetListCounter = 0;
var force;
var svg;
var color;
var mainSvgGraph;

var closeLeftFrame = false;
var closeRightFrame = false;
var closeMiddleFrame = false;

var saveJsonForm; // = document.forms['jsonSaver'];
var saveJsonValue; // = document.getElementById('saveJsonData');

var loadJsonForm; // = document.forms['jsonLoader'];
var loadJsonValue; // = document.getElementById('loadJsonData');


				
//~ localStorage.myProperty = "Hello World";
//~ console.log(localStorage.myProperty); //testing the local storage 


			var tempTextData; 
			var reader = new FileReader();

			reader.onload = function(e) 
			{
				tempTextData = reader.result;
				localStorage.myProperty = reader.result;  
				mainJsonFile  = JSON.parse(reader.result); 
				creaInit();
				//~ console.log(tempTextData);
			}

						function disableResend()
						{
							//~ alert("I am an alert box!");
							saveJsonForm = document.forms['jsonSaver'];

							saveJsonForm.disabled=true;
							//~ saveJsonValue = document.getElementById('saveJsonData');
							//~ saveJsonValue.value = JSON.stringify(mainJsonFile);
							//~ saveJsonForm.submit();
						}
						

						function saveJsonData()
						{
							//~ alert("I am an alert box!");
							
							saveJsonForm = document.forms['jsonSaver'];
							saveJsonForm.disabled=false;
							saveJsonValue = document.getElementById('saveJsonData');
							saveJsonValue.value = JSON.stringify(mainJsonFile);
							saveJsonForm.submit();
						}
						
						function loadJsonData()
							{
								loadJsonValue = document.getElementById('loadJsonFile');
								loadJsonValue.click(); 
							}
							
						function uploadFile()
						{
							
							var selectedFile = document.getElementById('loadJsonFile').files[0];
							//~ var filevar = new FileReader();
							//~ filevar.readAsText(selectedFile);
							//~ var playa = document.getElementById('playa').innerHTML = filevar.result;
							reader.readAsText(selectedFile);
							console.log(selectedFile);
							//~ console.log(filevar.readyState);
							//~ console.log(selectedFile.name);
							console.log(reader);
							//~ while
							
							//~ console.log(tempTextData);
						}
							
						//~ function loadJsonData()
						//~ {
							//~ alert("I am an alert box!");
							//~ loadJsonForm = document.forms['jsonLoader'];
							//~ loadJsonValue = document.getElementById('loadJsonData');
							//~ loadJsonValue.value = "EEE"; 
							//~ loadJsonForm.submit();
						//~ }

if (localStorage.myProperty)
{ 
		mainJsonFile = JSON.parse(localStorage.myProperty); //this makes sure that will will add this to the main simulation interface 
} 

						

function stayInBound(mainInteger, modulusInteger)
{
	return (mainInteger % modulusInteger); //return the modulus integer 
	
}


function shellOfAFunction() 
{ 
			localStorage.myProperty = JSON.stringify(mainJsonFile); 
			console.log(localStorage.myProperty); 
} 


function showRunSim()
{
	var i, text, tempTrashVar; 
	text = '<center>';	
	var frame = document.getElementById('middleGraphMenu'); //load the frame right here
	
	for (i = 0; i < mainJsonFile.lenth; i++)
	{
		text += mainJsonFile[i]["id"]; 
		text += mainJsonFile[i]["name"]; 
		
	}
	
	
	text += '</center>';
	text += '<br><br>'; //

	return text; //this is just right here for whatever
}


function snatchJsonDataFromTextArea() 
{ 
				var jsonTextElement = document.getElementById("mainSaveLoadTextArea").value; 
				if (jsonTextElement)
				{
					localStorage.myProperty = jsonTextElement;  
					mainJsonFile  = JSON.parse(jsonTextElement); 
					creaInit();
				}
				console.log("below is the actual passed text"); 
				console.log(jsonTextElement); 
				
				
				console.log("this below is actually the new html session property"); 
				console.log(localStorage.myProperty); 
				//~ simHours = document.getElementById("simHours").value 

} 

function SelectAll(id)
{
    document.getElementById(id).focus();
    document.getElementById(id).select();
}

function showLoadSim()
{
	
	/*
	var myWindow = window.open("", "MsgWindow", "width=640, height=480");
	text = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"'; 
	text += '"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">'; 
	text += '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">';
	text += '<head>';
	text += '<title>Load Sim Data</title>'
	text += '<meta http-equiv="content-type" content="text/html;charset=utf-8" />';
	text += '<meta name="generator" content="Geany 1.24" />'
	text += '</head>';
	text += '<body bgcolor="#6A1BA1">';
	//main text is below here: 
	//
	//
	* */
	
	//before anything make sure you save the data into the new html5 data save feature.. .
	
	
	var text; //just the text right here
	
	
	 
	var frame = document.getElementById('middleGraphMenu'); //load the frame right here
	text = '<center>';
	//~ text += '<script>';
	//~ text += 'function snatchJsonDataFromTextArea() { var jsonTextElement = document.getElementById("mainSaveLoadTextArea").value; if (jsonTextElement){ localStorage.myProperty = jsonTextElement;  } console.log(localStorage.myProperty); } ';
				//~ simHours = document.getElementById("simHours").value 
	//~ text += '</script>';
	//~ text += '<form>';
	
	
	text += '<br><br><h3><p>Paste your sim data here and click load, to load your simulation<p></h3>';
	text += '<textarea id="mainSaveLoadTextArea" name="mainSaveLoadTextArea" rows="25" cols="60" >';
	text += '</textarea>';
	
	
	
	text += '<br> <button type="button" onclick="snatchJsonDataFromTextArea()" > Load </button> '; //button right here 
	//~ text += localStorage.myProperty; //button right here 
	
	//~ text += '</form>';
	text += '</center>';
	text += '<br><br>'; //

	//~ myWindow.document.write(text);
	
	frame.innerHTML = text; //actually putting the text on to the frame 
	
	
	
	selectMiddleFrame("graph");  
	





} 

function showSaveSim()
{
	/*
	var myWindow = window.open("", "MsgWindow", "width=640, height=480");
	var text = '<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"'; 
	text += '"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">'; 
	text += '<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">';
	text += '<head>';
	text += '<title>Save Sim Data</title>'
	text += '<meta http-equiv="content-type" content="text/html;charset=utf-8" />';
	text += '<meta name="generator" content="Geany 1.24" />'
	text += '</head>';
	text += '<body bgcolor="#6A1BA1">';
	//main text is below here: 
	//
	//
	* */
	var text; //just the text right here
	
	localStorage.myProperty = JSON.stringify(mainJsonFile); //make sure to actually save the file right here  
	 
	var frame = document.getElementById('middleGraphMenu'); //load the frame right here	
	text = '<center>';
	text += '<br><br><h3><p>Copy and paste this within a text file to save your sim data<p></h3>';
	text += '<textarea id="mainSaveLoadTextArea" name="mainSaveLoadTextArea" rows="25" cols="60" onclick="this.focus();this.select()" readonly >';
	text += JSON.stringify(mainJsonFile); 
	text += '</textarea>';
	text += '</center>';
	text += '<br><br>'; //

	//~ myWindow.document.write(text);
	
	frame.innerHTML = text; //actually putting the text on to the frame 
	
	selectMiddleFrame("graph");  
	
} 

function startNewProject()
{
		if (!(confirm("Are You Sure You Want to Start a new project?"))) 
		{
			return false;
		}

		nodeCount = actionListCount = propertyCount = 1;
		mainJsonFile = false; 
		localStorage.myProperty = false; 
		creaInit();
		//~ writeSvgObjInSpace();
	
	
}

function runSimForm()
{
	//~ var simRun = document.getElementById("simRunForm"); 
	//~ simRun.submit();
	 //~ document.getElementById("myForm").submit();
	//~ document.getElementById("simRunForm").submit();
	
	
	var mainGraph = document.getElementById('middleGraphMenu');
	mainGraph.innerHTML = '<center><h3>Computing...</h3><br><img src="imgs/loading.gif" alt="Loading" height="64" width="64"></center>';
    // 1. Create XHR instance - Start
    var xhr;
    if (window.XMLHttpRequest) {
        xhr = new XMLHttpRequest();
    }
    else if (window.ActiveXObject) {
        xhr = new ActiveXObject("Msxml2.XMLHTTP");
    }
    else {
        throw new Error("Ajax is not supported by this browser");
    }
    // 1. Create XHR instance - End
    
    // 2. Define what to do when XHR feed you the response from the server - Start
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4) {
            if (xhr.status == 200 && xhr.status < 300) {
                //~ document.getElementById('').innerHTML = xhr.responseText;
            
            mainGraph.innerHTML = xhr.responseText;
            
            }
        }
    }
    // 2. Define what to do when XHR feed you the response from the server - Start

    //~ var userid = document.getElementById("userid").value;
    var simHours = document.getElementById("simHours").value;

    // 3. Specify your action, location and Send to the server - Start 
    xhr.open('POST', 'graphShower.php');
    xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhr.send("simHours=" + simHours);
    // 3. Specify your action, location and Send to the server - End
	
	graphSimSwitchHeader("sim");
}



// below is where we are writing the show methods of the applicaton 

/*
var conditionTemplate = { //this is the condition template right here 
                  "field":" ",
                  "relation":" ",
                  "value":" "	
};

var propertyTemplate = { //this is the property template right here 
			"name": " ",
            "type": " ",
            "value": " "
};
 
var actionTemplate = { //this is the template for the actions
	              "action_type":" ",
                  "target_id":" ",
                  "target_value":" "
}; 

var nodeTemplate = { //this is the node template 
	
	"id": " ",
    "name": " ",
    "synonyms": " ",
    "image": " ",
    "comment": " ",
    "properties": { },
    "action list":{ }	
	
};

var actionEncapsulationTemplate =  { //this is an encapsulation of the action and condition objects
	"actions": [{ }],
	"conditions": [{ }]
 }; 


*/

//~ globalX = globalY = globalSvgX = globalSvgY = 0;	//set everything to zero 
//~ nodeCount = actionListCount = propertyCount = 0;	//

//these are variables that close and open the frames on the application 
//
//
//


/* 
 *  this right here is a standard json definition... 
 *
 * */

function regardShuPrompt()
{
	
	//~ tumP1 =  tumP2 = tumP3 = null;  //setting this to null is just a safety percaution 
	
	var text = "<p>Hello Shu<p>";
	text += "<p>I am pleased to show you the application that I have been working on, this is a culmionation of my work and I think that you are going to enjoy it. Please take notice to the speed and elegacy that this interface holds to the creal simulator. I put a lot of work and emphasis into this project, as well as a lot of money, and non-profit contributions.<p>";
	text += "";	
	
	/*
	 * 
	 * This is the variation that we are going to use for shu in our creal version 
	 * 
	 * */ 
	
	
	return text; //returning the text variable to the application right here 
	
	
}



function selectRightFrame(switchVar)
{

	var frame = document.getElementById('rightFrame');
	if (frame) {
		if (switchVar == "show") {
			frame.style.display = "block";

		} else {
			frame.style.display = "none";

		}

	}
}

function clearAndHideRightFrame()
{

	var frame = document.getElementById('rightFrame');
	if (frame) {

		frame.style.display = "none";
		frame.innerHTML = " ";

	}
}

function selectMiddleFrame(switchVar)
{

	var frame = document.getElementById('middleFrame');
	var graphMiddleToggle = document.getElementById('middleGraphMenu');
	
	
	if (frame && graphMiddleToggle) {
		if (switchVar == "graph") {
			frame.style.display = "none";
			graphMiddleToggle.style.display = "block";
		}
		else
		{
			frame.style.display = "block";
			graphMiddleToggle.style.display = "none";
		}

	}

}

function showNodeAdd()
{

	var frame = document.getElementById('rightFrameProportion');

	if (frame) {
		frame.innerHTML =
		    '<h3>Add Node</h3><br><br><label>Enter a node name</lable><br><input type="textbox" id="nodeNameTxtBox"/> <br><br><br><br><button type="button" class="btn btn-primary" id="submitNodeChanges" onclick=addNode() >Submit</button>';

		selectRightFrame("show");
	} else {
		return false;

	}

}


function showNodeMod(selectedNode)
{

	var frame = document.getElementById('rightFrameProportion');
	//~ var frame = document.getElementById('rightFrameProportion');
	
	if (frame) {

		frame.innerHTML =
		    '<h3>Modify Node</h3><br><br><label>Enter a node name</lable><br><input type="textbox" id="nodeNameTxtBox"/> <br><br><br><br><button type="button" class="btn btn-primary" id="submitNodeChanges" onclick=modNode('
		    + selectedNode + ') >Submit</button>';
		selectRightFrame("show");
		
		
		var i, j, k;
		 i = j = k = 0;
		 
		var internalObject;

		var textBox = document.getElementById('nodeNameTxtBox')

		    if (textBox) {
			for (i = 0; i < mainJsonFile.length; i++) {

				internalObject = mainJsonFile[i];

				if (internalObject["id"] == selectedNode) {

					textBox.value = internalObject["name"];

					return true;	//everything is good right here 
				}

			}
		}
	} else {

		return false;

	}

}


//
function showPropAdd(selectedNode)
{



	if (!(selectedNode)) {
		return false;
	}			//this is just to short circuit it right here 

	var frame = document.getElementById('rightFrameProportion');
	if (frame) {
		frame.innerHTML =
		    '<h3>Add Property</h3><br><br><label>Enter a property name</lable><br><input type="textbox" id="propNameTxtBox"/>';
		frame.innerHTML +=
		    '<label>Enter property value</lable><br><input type="textbox" id="propValueTxtBox"/>'
		    frame.innerHTML +=
		    '<br><br><br><br><button type="button" class="btn btn-primary" id="submitNodeChanges" onclick=addProperty('+ selectedNode +') >Submit</button>'
		    selectRightFrame("show");
	} else {
		return false;

	}

}

function showPropMod(selectedNode, propId)
{
	
		if (!(selectedNode ||  propId)) { return false; } //bad 
		/* 
		 * 
		 *  this was completely ripped right here.. I really want to watch the 49ers game tonight ... 
		 * */ 
		 
		var i, j, k;
		 i = j = k = 0;
		 
		 
		 //~ selectedNode, propId
		//~ modProperty(selectedNode, propertyId)
		
		var frame = document.getElementById('rightFrameProportion');
		
		
		if (frame) {
			//only show this shit if its true
		frame.innerHTML =
		    '<h3>Modify this Property</h3><br><br><label>Enter a property name</lable><br><input type="textbox" id="propNameTxtBox"/>';
		frame.innerHTML +=
		    '<label>Enter property value</lable><br><input type="textbox" id="propValueTxtBox"/>'
		    frame.innerHTML +=
		    '<br><br><br><br><button type="button" class="btn btn-primary" id="submitNodeChanges" onclick=modProperty('+ selectedNode + ',' + propId +') >Submit</button>'				
					
				
				selectRightFrame("show");
			
		}
		
		else {
		
		return false;

	} 
}

function showPropDel(selectedNode, propId)
{
		//this function is deprecated, start using delProperty, eventually delete this	
	//~ if (!()) { return " "; } //bad 

	if (!(selectedNode ||  propId || confirm("Are You Sure You Want to Delete this Property?"))) {
		return false;


	}
	else
	{ 
		delProperty(selectedNode, propId); //you are going to want to call this function right here 
		
		updateLeftFrame();

		//this is where the payload is.. 
	} 
 
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 


function showActAdd(selectedNode, actionID)
{
	
		if (!(selectedNode ||  actionID)) { return " "; } //this is a template, but in relation to the action id .. .
		/* 
		 * 
		 *  this was completely ripped right here.. I really want to watch the 49ers game tonight ... 
		 * */ 
		 
		 
	console.log(selectedNode); 
	console.log(actionID); 
	 
		
	var j, k, i;
	j = i = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var text;
	//~ for (i = 0; i < inObj.length; i++) {

 
	var frame = document.getElementById('rightFrameProportion');
	
		//~ var actionStringTable = ["nonaction","Increase","Decrease","Change","Maintain","Transport","nonaction"]; 
	//~ var conditionStringTable = ["nonrelation", "=", ">", "<", ">=","<=","!="]; 
	//~ var conditionStringTable = ["nonrelation", "=", ">", "<", ">=","<=","!="]; 

	if (frame) 
	{ 
		frame.innerHTML = '<h3>Add Action</h3><br><br>';
		frame.innerHTML += ' 			<label>Select Action Type</label><br>';
		text = '<select id = "selectedActionType"> ';
		for (i = 1; i < 6; i++)
		{
			//~ frame.innerHTML += '<option value = "' + i.toString() + '">' + actionStringTable[i] + '</option>';
			text += '<option value =' + i.toString() + '> ' +
		    actionStringTable[i] + '</option>';

			
		}
		text += "</select><br><br>";	
		
		frame.innerHTML += text; 
		frame.innerHTML += '<label>Enter Selected Property ID</label> <br> <input type="textbox"id="selectedPropId"/> <br><br> ';
		frame.innerHTML += '<label>Enter Action Expression Value</label> <br> <input type="textbox"id="selectedActionValue"/> <br><br> ';
		frame.innerHTML += '<button type="button" class="btn btn-primary" id="submitNodeChanges" onclick="addAction('+ selectedNode +','+ actionID +')" >Submit</button>';
		
		selectRightFrame("show");
		
	} 
	else 
	{
		return false; //null
		 
	}

	//~ }
}

//~ function showActionMod(selectedAction)
//~ {
	//~ if (!(selectedAction)) {
		//~ return " ";
	//~ }			//bad
//~ 
//~ }
/*										<label>Condition Type</label>\
										<select id = "addConditionSelection">\
										<option value = "0"> != </option>\
										<option value = "1"> = </option>\
										<option value = "2"> > </option>\
										<option value = "3"> < </option>\
										<option value = "4"> >= </option>\
										<option value = "5"> <= </option>\
										</select>\

 * 
 * */
 
  
function showActMod(selectedNode, actionID, actionIndex)
{
	
	
	if (!(selectedNode ||  actionID || actionIndex)) { return " "; } //this is a template, but in relation to the action id .. .
		//~ /* 
		 //~ * 
		 //~ *  this was completely ripped right here.. I really want to watch the 49ers game tonight ... 
		 //~ * */ 
		 
	var inObj = mainJsonFile; 
	var intActionLists, intArray, text, innerKeys;
	console.log(selectedNode);
	console.log(actionID);
	console.log(actionIndex);
	if (!(inObj)) 
	{
				return "";
	}		//this makes sure we short circuit the function in its place right here                 
	
	var i, j, k;
	 i = j = k = 0;
		 
 
	var frame = document.getElementById('rightFrameProportion');
	
	if (frame) 
	{ 
	for (k = 0; k < inObj.length; k++)
	{
		inObject = inObj[k];
		
		if (selectedNode == inObject["id"]) 
		{
			//~ console.log(selectedNode);
	//~ console.log(actionID);
	//~ console.log(actionIndex);
			intActionLists = inObject["action list"];
			var intKeys = intActionLists[actionID];
			var intActionKeys = intKeys["actions"];
			innerKeys = intActionKeys[parseInt(actionIndex)];
			//~ console.log(intActionKeys);
			//~ intArray = Object.keys(intActionLists);
		frame.innerHTML = '<h3>Modify Action</h3><br><br>';
		frame.innerHTML += ' 			<label>Select Action Type</label><br>';
		text = '<select id = "selectedActionType"> ';
		for (i = 1; i < 6; i++)
		{
			//~ frame.innerHTML += '<option value = "' + i.toString() + '">' + actionStringTable[i] + '</option>';
			text += '<option value =' + i.toString() + '> ' +
		    actionStringTable[i] + '</option>';

			
		}
		text += "</select><br><br>";	
		frame.innerHTML += text;
		frame.innerHTML += '<label>Enter Selected Property ID</label> <br> <input type="textbox"id="selectedPropId"/> <br><br> ';
		frame.innerHTML += '<label>Enter Action Expression Value</label> <br> <input type="textbox"id="selectedActionValue"/> <br><br> ';
		frame.innerHTML += '<button type="button" class="btn btn-primary" id="submitNodeChanges" onclick="addAction('+ selectedNode +','+ actionID +')" >Submit</button>';
		var selectedPropID = document.getElementById('selectedPropId');
		var selectedActionValue = document.getElementById('selectedActionValue');
		selectedPropID.value = innerKeys["target_id"];
		selectedActionValue.value = innerKeys["target_value"];
		selectRightFrame("show");
		return true;
		}
	}	
	} 
	else 
	{
		return " "; //null
		 
	}


	

}

function showActDel(selectedNode, actionID, actionIndex)
{
	
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // 

function showCondAdd(selectedNode, actionID)
{
		var i, j, k, text;
		 i = j = k = 0;

		console.log(selectedNode); //actionID
		console.log( actionID);		 
	
	if (!(selectedNode ||  actionID)) { return " "; } //this is a template, but in relation to the action id .. .
	
	var frame = document.getElementById('rightFrameProportion');
	
	
	if (frame) 
	{ 
		
		
		frame.innerHTML = '<label>Add Conditions</label><br><br>';
		frame.innerHTML += '<label>Enter Selected Field</label><br>';
		frame.innerHTML += '<input type="textbox"id="selectedConditionField"/><br>';
		
		
		frame.innerHTML += '<label>Select Relation</label><br>';
		
		text = '<select id = "selectedConditionType"> ';
		for (i = 1; i < 7; i++)
		{
			//~ frame.innerHTML += '<option value = "' + i.toString() + '">' + actionStringTable[i] + '</option>';
			text += '<option value =' + i.toString() + '> ' +
		    conditionStringTable[i] + '</option>';

			
		}
		text += "</select><br><br>";	
		
		frame.innerHTML += text; //make sure to add the dropbox
		
		frame.innerHTML += '<label>Enter Selected Value</label><br>';
		frame.innerHTML += '<input type="textbox"id="selectedConditionValue"/><br>';

		
		frame.innerHTML += '<button type="button" class="btn btn-primary" id="submitNodeChanges" onclick="addCondition('+ selectedNode +' ,'+ actionID + ')" >Submit</button>';

		selectRightFrame("show");
	}
	else
	{
		
		
	}
}

function showCondMod(selectedNode, actionID, conditionIndex)
{
	
		if (!(selectedNode ||  actionID || conditionIndex)) { return " "; } //this is a template, but in relation to the action id .. .
		
		var i, j, k, text;
		 i = j = k = 0;
		 
 
	var frame = document.getElementById('rightFrameProportion');
	var conditionValue, conditionTargetId, conditionComparison; 
	conditionValue = conditionTargetId = conditionComparison = null; //this is really cool right here as usual 
	
	
	if (frame) 
	{ 
		for (k = 0; k < inObj.length; k++)
		{
			inObject = inObj[k];
			
			if (selectedNode == inObject["id"]) 
			{
							frame.innerHTML = '<label>Add Conditions</label><br><br>';
					frame.innerHTML += '<label>Enter Selected Field</label><br>';
					frame.innerHTML += '<input type="textbox"id="selectedConditionField"/><br>';
					
					
					frame.innerHTML += '<label>Select Relation</label><br>';
					
					text = '<select id = "selectedConditionType"> ';
					for (i = 1; i < 7; i++)
					{
						//~ frame.innerHTML += '<option value = "' + i.toString() + '">' + actionStringTable[i] + '</option>';
						text += '<option value =' + i.toString() + '> ' +
						conditionStringTable[i] + '</option>';

						
					}
					text += "</select><br><br>";	
					
					frame.innerHTML += text; //make sure to add the dropbox
					
					frame.innerHTML += '<label>Enter Selected Value</label><br>';
					frame.innerHTML += '<input type="textbox"id="selectedConditionValue"/><br>';

					
					frame.innerHTML += '<button type="button" class="btn btn-primary" id="submitNodeChanges" onclick="modAction('+ selectedNode + ',' + actionID + ',' + conditionIndex +')" >Submit</button>';
					selectRightFrame("show");
					return true;
			}
		}
			

		
	}
	else
	{
		
		return false; 
	}
}

function showCondDel(selectedNode, actionID, conditionIndex)
{
	//this function is deprecated, instead use delCondition().. if this function does not exist then please create it
}



//~ new svgNodeConnect();
/*
internalNodeConnection.push(new svgNodeConnect());
internalNodeConnection.push(new svgNodeConnect());
internalNodeConnection.push(new svgNodeConnect());
*/

//~ console.log(internalNodeConnection);

function graphSimSwitchHeader(switchType, documentObject)
{

	var frame = document.getElementById('simHeaderDiv');

	if (!(frame)) {
		return -1;
	}			//bad 
	if (!(switchType)) {
		return -1;
	}

	var text = null;

	text = '<ul class="nav nav-tabs" role="tablist">';

	if (switchType == "sim") {

		text +=
		    '<li><a href="#" onclick=graphSimSwitchHeader("vis") >Visual</a></li>';
		text +=
		    '<li class="active"><a href="#" onclick=graphSimSwitchHeader("sim") >Simulation</a></li>';
		visualOrSimState = "sim";
		selectMiddleFrame("graph");
	} else if (switchType == "vis") {

		text +=
		    '<li class="active" ><a href="#" onclick=graphSimSwitchHeader("vis") >Visual</a></li>';
		text +=
		    '<li><a href="#" onclick=graphSimSwitchHeader("sim") >Simulation</a></li>';
		visualOrSimState = "vis";
		selectMiddleFrame("vis");
	} else {

		text +=
		    '<li class="active" ><a href="#" onclick=graphSimSwitchHeader("vis") >Visual</a></li>';
		text +=
		    '<li><a href="#" onclick=graphSimSwitchHeader("sim") >Simulation</a></li>';
		visualOrSimState = "vis";
		selectMiddleFrame("vis");
	}

	text += '</ul>';

	frame.innerHTML = text;
	return text;
}

function changeState(switchType, documentObject)	// // // // 
{
	if (!(switchType)) {
		return -1;
	}

	var text = null;

	text = '<ul class="nav nav-tabs" role="tablist">';

	if (switchType == "sim") {

		text +=
		    '<li><a href="#" onclick=graphSimSwitchHeader("vis") >Visual</a></li>';
		text +=
		    '<li class="active"><a href="#" onclick=graphSimSwitchHeader("sim") >Simulation</a></li>';
		visualOrSimState = "sim";

	} else if (switchType == "vis") {

		text +=
		    '<li class="active" ><a href="#" onclick=graphSimSwitchHeader("vis") >Visual</a></li>';
		text +=
		    '<li><a href="#" onclick=graphSimSwitchHeader("sim") >Simulation</a></li>';
		visualOrSimState = "vis";

	} else {

		text +=
		    '<li class="active" ><a href="#" onclick=graphSimSwitchHeader("vis") >Visual</a></li>';
		text +=
		    '<li><a href="#" onclick=graphSimSwitchHeader("sim") >Simulation</a></li>';
		visualOrSimState = "vis";

	}

	text += '</ul>';

	return text;

}

function loadEnvironment(inObj)
{
	//this function loads the environment
	//this is the main function of the program, it loads everything from a given json file 
	if (!(inObj)) {
	return -1};		//this makes sure we short circuit the function in its place right here              

	var i, j, k, l, m;
	i = j = k = l = m = 0;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var variableNumber0 = 0;
	var variableNumber1 = 0;
	nodeCount = actionListCount = propertyCount = 1;	//

	
	
	for (i = 0; i < inObj.length; i++) {

		inObject = inObj[i];

		if (i == 0) {

			initialNode = inObject["id"];	// this is what we do when we initialize the application 

		}

		variableNumber0 = parseInt(inObject["id"]);
		if (variableNumber0 > nodeCount) {
			nodeCount = variableNumber0;

		}
		//right now we are grabbing the data 
		intProperties = inObject["properties"];
		intActionLists = inObject["action list"];

		//properties
		console.log(inObject);
		console.log(intProperties);
		intArray = Object.keys(intProperties);

		if (intProperties) {
			for (k = 0; k < Object.keys(intProperties).length; k++) {
				// this is for the properties

				variableNumber0 = parseInt(intArray[k]);
				if (variableNumber0 > propertyCount) {
					propertyCount = variableNumber0;

				}

			}
		}

		//actions
		intArray = Object.keys(intActionLists);
		if (intActionLists) {
			for (j = 0; j < Object.keys(intActionLists).length; j++) {

				//this is for the action lists

				//~ console.log(intActionLists[intArray[j]]);
				intKeys = intActionLists[intArray[j]];

				variableNumber0 = parseInt(intArray[j]);
				if (variableNumber0 > actionListCount) {
					actionListCount = variableNumber0;

				}
				//~ console.log(intKeys["actions"]);

			}
		}
	}

	//this is an incrementation. Pointing to the next node
	nodeCount++;
	actionListCount++;
	propertyCount++;	//

	return 1;		//everything is good.
}

//~ internalNodeConnection[10];




function registerObject(inObj)
{

	inObj = null;		//do nothing 

	return;

}




function writeSvgObjInSpace()
{
	buildTargetList(mainJsonFile);//generate target list 
	generateNodeList(mainJsonFile); //generate entire object 
	generateGraphViz();
	
	console.log(targetList);
	return 1;		//everything went good right here 



}

			//testing out this object right here

	//this is added right here to change the format of the code

//Debug
//~ mainJsonFile = currentDemoJson;

if (demoVar == true) {

	mainJsonFile = currentDemoJson;

}


//~ console.log(mainJsonFile);	//this right here is used for debugging.. 


function debugObj(inObj)
{

	//~ inObj.forEach(
	//~ var length = inObj.length; 
	var i, j, k, l, m;
	i = j = k = l = m = 0;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;

	if (!(inObj)) {
	return};		//this makes sure we short circuit the function in its place right here                 

	for (i = 0; i < inObj.length; i++) {
		//~ console.log(inObj[i].name);
		inObject = inObj[i];

		console.log(inObject["id"]);
		console.log(inObject["comment"]);
		console.log(inObject["image"]);
		console.log(inObject["location"]);
		console.log(inObject["synonyms"]);

		//right now we are grabbing the data 
		intProperties = inObject["properties"];
		intActionLists = inObject["action list"];

		//properties
		console.log(Object.keys(intProperties));
		intArray = Object.keys(intProperties);

		if (intProperties) {
			for (k = 0; k < Object.keys(intProperties).length; k++) {
				// this is for the properties
				console.log(intArray[k]);
				console.log(intProperties[intArray[k]]);
				intKeys = intProperties[intArray[k]];
				console.log(intKeys["name"]);
				console.log(intKeys["type"]);
				console.log(intKeys["value"]);
			}
3		}

		//actions
		console.log(Object.keys(intActionLists));
		intArray = Object.keys(intActionLists);

		if (intActionLists) {

			for (j = 0; j < Object.keys(intActionLists).length; j++) {

				//this is for the action lists
				console.log(intArray[j]);
				//~ console.log(intActionLists[intArray[j]]);
				intKeys = intActionLists[intArray[j]];

				//~ console.log(intKeys["actions"]);

				intActionKeys = intKeys["actions"];
				intConditionKeys = intKeys["conditions"];

				if (intActionKeys) {
					for (l = 0; l < intActionKeys.length; l++) {	//this goes through the list of actions
						console.log(intActionKeys[l]);
						intKeys = intActionKeys[l];

						console.
						    log(intKeys["action_type"]);
						console.
						    log(intKeys["target_id"]);
						console.
						    log(intKeys
							["target_value"]);
					}
				}
				if (intConditionKeys) {
					//conditions right here 
					for (l = 0; l < intConditionKeys.length; l++) {	//this goes through the list of actions
						console.
						    log(intConditionKeys[l]);
						intKeys = intConditionKeys[l];

						console.log(intKeys["field"]);
						console.
						    log(intKeys["relation"]);
						console.log(intKeys["value"]);
					}
				}
			}
		}
	}

}

/*
function loadNode(nodeId)
{
	
	//this function is used to load the node into the javascript context screen
3	
	
	//~ if (selectedNode == )
	//~ {
		//~ 
		//~ 
	//~ }
	
}
*/

function writePropSvg(name,propertyKey,nodeIndex)
{
	
							targetList[parseInt(propertyKey)] = targetListCounter; //for the target list 
							graph["nodes"][targetListCounter] = returnGraphNameObject(name,nodeIndex);
							targetListCounter++;
}

function addToActionList(inObj, actionObject)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}
	if (!(inObj)) {
	return};		//this makes sure we short circuit the function in its place right here                 
	actionListCount++;
	inObj.push(actionObject);

}

function addProperty(selectedNode)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return "demo";
	}

	inObj = mainJsonFile; 

	var  i, j, k;
	i = j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intAction;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;


	if (!(inObj)) {
	return false; 
	 };		//this makes sure we short circuit the function in its place right here                 
	
    
	//~ var propValue = document.getElementById(); 
	//~ var propName = document.getElementById(); 
	
	//~ console.log(trueProperties); //this is for debugging right here 
		
		/*
		 * Right here we are going to add the things we need to allow the property to 
		 * 
		 * */ 
		 
		 var propName = document.getElementById("propNameTxtBox"); 
		 var propValue = document.getElementById("propValueTxtBox"); 
		 
		 
				//~ actions.push(actionTemplate); 
	//~ intActionLists[actionListCount.toString()] = actionListProtoType;	
			if (propName && propValue) 
			{
				
			var propertyTemplate = {
            "name": "",
            "type": "number",
            "value": ""
        }; 
				
				
				propertyTemplate['name'] = propName.value; 
				propertyTemplate['value'] = propValue.value;
				 
				var propNumString =  propertyCount.toString(); 
				var  trueProperties = {};
				
				trueProperties[propNumString] = propertyTemplate;

				for (i = 0; i < inObj.length; i++) 
				{
					
					internalObject = inObj[i];
					console.log(internalObject);

					console.log(selectedNode); 	
					
					if (internalObject["id"] == selectedNode) 
					{
						console.log(internalObject["id"]); 
						//~ internalObject["properties"].push(properties);
						 //~ intProperties = internalObject["properties"]; 
							if (!(internalObject["properties"]))
							{
								internalObject["properties"] = {};  
								intProperties = internalObject["properties"];
								intProperties[propertyCount.toString()] = propertyTemplate;
								//~ intProperties
							}
							else
							{
								//~ internalObject["properties"] += propertyTemplate;
								console.log(intProperties);
								 
								intProperties = internalObject["properties"];
								intProperties[propertyCount.toString()] = propertyTemplate;
							}
							//~ console.log(intAction);
							//~ updateLeftFrame();
						
									selectRightFrame("close");
									
									targetList[propertyCount] = internalObject["id"]; // this is used to get the right shit 
									updateLeftFrame();
									propertyCount++; //make sure to update the property count
							return true; //exit out of the application right here 
					}
						
					
				}
			//~ inObj.push(propertyObject);
			}
			//~ writeSvgObjInSpace();
}

function addAction(selectedNode, selectedActionList)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}

	inObj = mainJsonFile; 
	console.log(inObj); 
	console.log(selectedNode); 
	console.log(selectedActionList); 
	//~ if (!(selectedNode || selectedActionList )) {
	//~ return " "; 
				//~ };		//this makes sure we short circuit the function in its place right here                 
	
		//~ inObj = mainJsonFile;
	
	var  i, j, k;
	i = j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intAction;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;


	var actionType, targetId, targetValue; 
	
	actionType = document.getElementById("selectedActionType");
	targetValue = document.getElementById("selectedActionValue");
	targetId = document.getElementById("selectedPropId");
	
	//~ console.log(actionType);
	//~ console.log(targetValue);
	//~ console.log(targetId);
	
	if (!(actionType || targetId || targetValue)) { return false; }
	
	

	var intActionType = actionType.options[actionType.selectedIndex].value;

	var intTargetId = targetId.value;
	var intTargetValue = targetValue.value;


	var actionTemplate = { 
				//this is the template for the actions
	              "action_type":" ",
                  "target_id":" ",
                  "target_value":" "
						};



		actionTemplate["target_id"] = intTargetId;
		actionTemplate["target_value"] = intTargetValue;
		actionTemplate["action_type"] = intActionType;

			var actions = []; 
				actions.push(actionTemplate); 
				
	for (i = 0; i < inObj.length; i++) 
	{
		
		console.log(internalObject);
		internalObject = inObj[i];

		
		if (internalObject["id"] == selectedNode) 
		{
				intActionLists = internalObject["action list"];
				
				intAction = intActionLists[selectedActionList]; 
				if (!(intAction["actions"]))
				{
					
				intAction["actions"] = actions;
					
				}
				else
				{
				intAction["actions"].push(actionTemplate); 
 				console.log(intAction);
				}
				//~ updateLeftFrame();
			
						selectRightFrame("close");
						//~ mainSvgGraph.addLink(internalObject["id"],targetList[parseInt(actionTemplate["target_id"])],5);
						//~ console.log(mainSvgGraph); 
						//~ console.log(actionTemplate["target_id"]); 
						//~ console.log(targetList[parseInt(actionTemplate["target_id"])]); 
						//~ console.log(targetList);
						updateLeftFrame();
				return true; //exit out of the application right here 
		}
			
		
	}
	//~ inObj.push(propertyObject);
	//~ writeSvgObjInSpace();
}

function addCondition(selectedNode, selectedActionList)
{
	
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}
	
	inObj = mainJsonFile; 
	console.log(inObj); 
	console.log(selectedNode); 
	console.log(selectedActionList); 
	//~ if (!(selectedNode || selectedActionList )) {
	//~ return " "; 
				//~ };		//this makes sure we short circuit the function in its place right here                 
	
		//~ inObj = mainJsonFile;
	
	var  i, j, k;
	i = j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intAction;
	var intConditionKeys;
	var intConditions;
	var intArray;
	var nodeSvgString;

	if (!( selectedNode ||  selectedActionList)) { return  " ";}  //short circuit
	
	
	
			var conditionTemplate = { //this is the condition template right here 
                  "field":" ",
                  "relation":" ",
                  "value":" "	
				};
				
				//below here are the fields that are needed to be used
				
				var conditions = []; 
				
	//this is where we grab the data in relation to the actual conditions on the form of the page 
	var selectedConditionType = document.getElementById('selectedConditionType');
	var selectedConditionValue = document.getElementById('selectedConditionValue');
	var selectedConditionField = document.getElementById('selectedConditionField');
	console.log(selectedConditionType);
	console.log(selectedConditionValue);
	console.log(selectedConditionField);
	

	if (selectedConditionField && selectedConditionValue && selectedConditionType)
	{
			conditionTemplate["field"] = selectedConditionField.value; 
			conditionTemplate["relation"]  =  selectedConditionType.options[selectedConditionType.selectedIndex].value;	//assign this value right here 
			conditionTemplate["value"] = selectedConditionValue.value; 
				
				conditions.push(conditionTemplate); 
				for (i = 0; i < inObj.length; i++) 
					{
						
						console.log(internalObject);
						internalObject = inObj[i];

						
						if (internalObject["id"] == selectedNode) 
						{
								intActionLists = internalObject["action list"];
								
								intConditions = intActionLists[selectedActionList]; 
								console.log(intActionLists);
								console.log(intConditions); 
								if (!(intConditions["conditions"]))
								{	
									//~ intConditions += conditions;
									//~ intConditions["conditions"] = conditionTemplate; 
									//~ intActionLists[selectedActionList] += conditions;
									intConditions["conditions"] = conditions; 
									console.log(intConditions);
									//~ intConditions.push(conditions); 
								}
								else
								{
									
									intConditions["conditions"].push(conditionTemplate); 
									
								}
								//~ return;
								//~ intConditions["conditions"] = conditionTemplate; 
								//~ console.log(intAction);
								//~ updateLeftFrame();
							
										selectRightFrame("close");
						
										updateLeftFrame();
								return true; //exit out of the application right here 
						}
							
						
					}
		
	}
	else
	{
			alert("Not all values were entered into the the right menu!"); //this is bad right here.. make sure they enter something
			return false; 
	}	
	//~ for (
}

function removeActionListProperty(inObj, idOrNameToRemove, removalType)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}
	
	if (!(inObj)) {
		return "";
	};			//this makes sure we short circuit the function in its place right here             

	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;

	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];

		intProperties = internalObject["properties"];

		intActionLists = internalObject["action list"];

		if (removalType == "property") {
			if (intProperties) {
				for (k = 0;
				     k < Object.keys(intProperties).length;
				     k++) {
					// this is for the properties
					intArray = Object.keys(intProperties);

					if (intArray[k] == idOrNameToRemove) {
						removalIndex = k;

						intProperties.
						    splice(removalIndex, 1);

					}

				}

			}

		} else if (removalType == "action_list") {
			if (intActionLists) {

				for (k = 0;
				     k < Object.keys(intActionLists).length;
				     k++) {
					// this is for the properties
					intArray = Object.keys(intActionLists);

					if (intArray[k] == idOrNameToRemove) {
						removalIndex = k;

						intActionLists.
						    splice(removalIndex, 1);

					}

				}

			}

		} else if (removalType == "action") {
			if (i == idOrNameToRemove) {
				removalIndex = i;
				inObj.splice(removalIndex, 1);
				break;
			}

		} else if (removalType == "condition") {
			if (i == idOrNameToRemove) {
				removalIndex = i;
				inObj.splice(removalIndex, 1);
				break;
			}

		}

		else if (removalType == "node") {
			if (internalObject["id"] == idOrNameToRemove) {

				removalIndex = i;
				inObj.splice(removalIndex, 1);
				break;
			}

		} else {

			return -1;

		}

	}

	return 1;

}



/*
function removeNodeActionCondition(inObj, idOrNameToRemove, removalType)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}
	
	if (!(inObj)) {
		return -1;
	};			//this makes sure we short circuit the function in its place right here             

	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;

	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];

		if (removalType == "action") {
			if (i == idOrNameToRemove) {
				removalIndex = i;
				inObj.splice(removalIndex, 1);
				break;
			}

		} else if (removalType == "condition") {
			if (i == idOrNameToRemove) {
				removalIndex = i;
				inObj.splice(removalIndex, 1);
				break;
			}

		}

		else if (removalType == "node") {
			if (internalObject["id"] == idOrNameToRemove) {

				removalIndex = i;
				inObj.splice(removalIndex, 1);
				break;
			}

		} else {

			return -1;

		}

	}

	return 1;
}

// I don't think this constructor is actually needed anymore.	
function crealNodeObject(objNode)
{
	//this is the main object for javascript 
	this.objNode = objNode; //internal add objnode 
	this.addProperty = addProperty; //internal add property 
	this.addAction = addAction; //internal add action
	
	properties = []; //this is an array of properties 
	
	actions =[]; //this is an array of actions 
	var dom; //this is the associated document object variable.. 
}
*/



function displayRightFrameHeader(menuType, selectionType, nodeNumber)
{

	var topText = null;
	var bottomText = null;
	var menuActiveText = null;
	//~ var interlTextLayer1 = null; 
	//~ var interlTextLayer2 = null; 

	//this is the top text right here 
	topText = '<center><ul class="nav nav-tabs">';

	//conditionals right here 
	if (menuType == "add") {
		menuActiveText =
		    '<li class="active" ><a href="#" onclick=mTypeSel("add")>Add</a></li>\
						<li ><a href="#" onclick=mTypeSel("del")>Delete</a></li>\
						<li ><a href="#" onclick=mTypeSel("mod")>Modify</a></li>\
						<li ><a href="#" onclick=mTypeSel("run")>Run</a></li>';
	} else if (menuType == "del") {
		menuActiveText =
		    '<li ><a href="#" onclick=mTypeSel("add")>Add</a></li>\
						<li class="active"><a href="#" onclick=mTypeSel("del")>Delete</a></li>\
						<li ><a href="#" onclick=mTypeSel("mod")>Modify</a></li>\
						<li ><a href="#" onclick=mTypeSel("run")>Run</a></li>';

	} else if (menuType == "mod") {
		menuActiveText =
		    '<li ><a href="#" onclick=mTypeSel("add")>Add</a></li>\
						<li ><a href="#" onclick=mTypeSel("del")>Delete</a></li>\
						<li class="active"><a href="#" onclick=mTypeSel("mod")>Modify</a></li>\
						<li ><a href="#" onclick=mTypeSel("run")>Run</a></li>';

	} else if (menuType == "run") {
		menuActiveText =
		    '<li ><a href="#" onclick=mTypeSel("add")>Add</a></li>\
						<li ><a href="#" onclick=mTypeSel("del")>Delete</a></li>\
						<li ><a href="#" onclick=mTypeSel("mod")>Modify</a></li>\
						<li class="active"><a href="#" onclick=mTypeSel("run")>Run</a></li>';

	} else {
		menuActiveText =
		    '<li class="active" ><a href="#" onclick=mTypeSel("add")>Add</a></li>\
						<li ><a href="#" onclick=mTypeSel("del")>Delete</a></li>\
						<li ><a href="#" onclick=mTypeSel("mod")>Modify</a></li>\
						<li ><a href="#" onclick=mTypeSel("run")>Run</a></li>';

	}

	bottomText = '</ul></center>';

	return topText + menuActiveText + bottomText;

}

function displayRightFrameSelection(menuType, selectionType, nodeNumber)
{

	var topText = null;
	var bottomText = null;
	var menuActiveText = null;
	//~ var interlTextLayer1 = null; 
	//~ var interlTextLayer2 = null; 

	//this is the top text right here 
	topText = '<label>Type</label> <br>';

	//conditionals right here 
	if (selectionType == "nodes") {
		menuActiveText = '<label>Nodes</label>\
									<input type = "radio" checked="checked" name="nodeActPropRadio"  id = "nodesRadio" value = "0" onclick=sTypeSel("nodes") />\
									<label>Actions</label>\
									<input type = "radio" name="nodeActPropRadio" id = "actionsRadio" value = "1" onclick=sTypeSel("actions") />\
									<label>Properties</label>\
									<input type = "radio" name="nodeActPropRadio"  id = "propertiesRadio" value = "2" onclick=sTypeSel("properties") />';

	} else if (selectionType == "actions") {
		menuActiveText = '<label>Nodes</label>\
									<input type = "radio" name="nodeActPropRadio"  id = "nodesRadio" value = "0" onclick=sTypeSel("nodes") />\
									<label>Actions</label>\
									<input type = "radio" checked="checked" name="nodeActPropRadio" id = "actionsRadio" value = "1" onclick=sTypeSel("actions") />\
									<label>Properties</label>\
									<input type = "radio" name="nodeActPropRadio"  id = "propertiesRadio" value = "2" onclick=sTypeSel("properties") />';

	} else if (selectionType == "properties") {
		menuActiveText = '<label>Nodes</label>\
									<input type = "radio" name="nodeActPropRadio"  id = "nodesRadio" value = "0" onclick=sTypeSel("nodes") />\
									<label>Actions</label>\
									<input type = "radio" name="nodeActPropRadio" id = "actionsRadio" value = "1" onclick=sTypeSel("actions") />\
									<label>Properties</label>\
									<input type = "radio" checked="checked" name="nodeActPropRadio"  id = "propertiesRadio" value = "2" onclick=sTypeSel("properties") />';

	} else {

		menuActiveText = '<label>Nodes</label>\
									<input type = "radio" checked="checked" name="nodeActPropRadio"  id = "nodesRadio" value = "0" onclick=sTypeSel("nodes") />\
									<label>Actions</label>\
									<input type = "radio" name="nodeActPropRadio" id = "actionsRadio" value = "1" onclick=sTypeSel("actions") />\
									<label>Properties</label>\
									<input type = "radio" name="nodeActPropRadio"  id = "propertiesRadio" value = "2" onclick=sTypeSel("properties") />';

	}

	bottomText = '';

	return topText + menuActiveText + bottomText;

}

function nodeInfoToLeftFrame(inObj, nodeId)
{
	if (!(nodeId)) {
		return " ";
	}			//make sure we exit outside of the function right here 
	if (!(inObj)) {
		return " ";
	}			//make sure we exit outside of the function right here 

	var i, j, k;
	i = j = k = 0;
	
	/*
	 * 
	 * 
 #define NONRELATION 0 //no action 
 #define EQUAL 1 //used for addition 
 #define GREATERTHAN 2 //used for deletion 
 #define LESSERTHAN 3 //used for changing 
 #define GREATERTHANEQUALTO 4 //used for maintaining 
 #define LESSERTHANEQUALTO 5 //used for transporting 
 #define NOTEQUAL 6 //used for transporting 
  
 #define NONACTION 0 //no action 
 #define INCREASE 1 //used for addition 
 #define DECREASE 2 //used for deletion 
 #define CHANGE 3 //used for changing 
 #define MAINTAIN 4 //used for maintaining 
 #define TRANSPORT 5 //used for transporting 
 #define NOTEQUAL 6 //used for transporting 
  
	 * 
	 * */
	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
		//~ (selectedNode, actionID)
	var text = "<dl>";

	for (i = 0; i < inObj.length; i++) {
		//~ console.log(inObj[i].name);
		inObject = inObj[i];

		if (nodeId == inObject["id"]) {
						text += "<dd><b>Node</b></dd>";
			text +=
			    "<dd>" + inObject["name"] + "<br>Node ID: " +
			    inObject["id"];
			text += "<dd>";
			
					text +=
						'<a href="#"><object data="imgs/mod.png" width="12" height="12" title="Modify Node" href="#" onclick="showNodeMod('
						+ inObject["id"] + ');"></object></a>';
			
					text +=
						'<a href="#"><object data="imgs/cross.png" width="12" height="12" title="Remove Node" href="#" onclick="delNode('
						+ inObject["id"] + ');"></object></a>  <br><br>';
					
			intProperties = inObject["properties"];
			intActionLists = inObject["action list"];
			intArray = Object.keys(intProperties);
			text += "<dd> Properties </dd> ";
			
			text += '<a href="#"><object data="imgs/plus.png" width="12" height="12" title="Add a property" href="#" onclick="showPropAdd('+ inObject["id"] +')";"></object></a>';
			
			//~ showPropDel(selectedNode, propId)
			
			if (intProperties) {
				for (k = 0; k < intArray.length; k++) {
			
					//~ // this is for the properties
			//~ 
					text +=
					    "<dd> Property ID: " + intArray[k] +
					    "</dd>";

					intKeys = intProperties[intArray[k]];
					text +=
					    "<dt> Name : " + intKeys["name"] +
					    "</dt>";
					
					/*text +=
					    "<dt> Type : " + intKeys["type"] +
					    "</dt>"; */
					    
					text +=
					    "<dt> Value : " + intKeys["value"] +
					    "<dt>";
					text +=
						'<a href="#"><object data="imgs/mod.png" width="12" height="12" title="Modify Property" href="#" onclick="showPropMod('
						+ inObject["id"] + ','+ intArray[k]+');"></object></a>';
				
					text += '<a href="#"><object data="imgs/cross.png" width="12" height="12" title="Remove Property" href="#" onclick="delProperty('+ inObject["id"] + ' , ' + intArray[k] +')";"></object></a>  <br><br>';
				}
				
			
			
			}
				//~ text += "<br><br>";
			

			//~ text += "<br>";

			//~ text += "<br>";
			intArray = Object.keys(intActionLists);
			//below here are the action lists
			
			text += "<dd> Action Lists </dd> ";
			text += '<a href="#"><object data="imgs/plus.png" width="12" height="12" title="Add an Action Group" href="#" onclick="addActionList('
					    + inObject["id"] + '' + ');"></object></a>';
			
			text += "<br><br> ";
			
			
			if (intActionLists) {

				for (j = 0; j < intArray.length; j++) {

					text +=

					    "<dd> Action ID: " + intArray[j] +
					    "<dd>";
					intKeys = intActionLists[intArray[j]];
			
					text +=
					    '<a href="#"><object data="imgs/cross.png" width="12" height="12" title="Remove Action Group" href="#" onclick="delActionList('+ inObject["id"] + ',' + intArray[j] +');"></object></a> <br><br>';
					
					intActionKeys = intKeys["actions"];
					intConditionKeys =
					    intKeys["conditions"];

					text += "<dd> Actions <dd> ";
					
					text +=
					    '<a href="#"><object data="imgs/plus.png" width="12" height="12" title="Add an Action" href="#" onclick="showActAdd('
					    + inObject["id"] + ',' + intArray[j] + ');"></object></a>';
								    
					if (intActionKeys) {
						for (l = 0; l < intActionKeys.length; l++) {	//this goes through the list of actions

							intKeys =
							    intActionKeys[l];
							text +=
							    "<dt> Action Type : "
							    +
							    actionStringTable[stayInBound(parseInt(intKeys["action_type"]), 7)] +
							    "<dt>";
							text +=
							    "<dt> Target ID : "
							    +
							    intKeys["target_id"]
							    + "<dt>";
							text +=
							    "<dt> Target Value : "
							    +
							    intKeys
							    ["target_value"] +
							    "<dt>";
						text +=
						    '<a href="#"><object data="imgs/mod.png" width="12" height="12" title="Modify Action" href="#" onclick="showActMod('
						    + inObject["id"] + ',' + intArray[j] + ',' + l.toString() +
						    ');"></object></a>';
						text +=
						    '<a href="#"><object data="imgs/minus.png" width="12" height="12" title="Remove Action" href="#" onclick="delAction('+ inObject["id"] + ',' + intArray[j] + ',' + l.toString() +');"></object></a>';
			
						text += "<br>";
						
						}
			
						
					}
					text += "<br>";

					text += "<dd> Conditions <dd>";

					text +=
					    '<a href="#"><object data="imgs/plus.png" width="12" height="12" title="Add a Condition" href="#" onclick="showCondAdd('
					    + inObject["id"] + ',' + intArray[j] +
					    ');"></object></a>';
				
					if (intConditionKeys) {
						//conditions right here 
						for (l = 0; l < intConditionKeys.length; l++) {	//this goes through the list of actions

							intKeys =
							    intConditionKeys[l];
							text +=
							    "<dt> Field : " +
							    intKeys["field"] +
							    "<dt>";
							text +=
							    "<dt> Relation : " +
							    //~ intKeys[""]
							     conditionStringTable[stayInBound(parseInt(intKeys["relation"]), 7)] 
							    + "<dt>";
							text +=
							    "<dt> Value : " +
							    intKeys["value"] +
							    "<dt>";
			
							text +=
							    '<a href="#"><object data="imgs/mod.png" width="12" height="12" title="Modify Condition" href="#" onclick="showCondMod('
							    + inObject["id"] + ',' + intArray[j] + ',' + l.toString() +
							    ');"></object></a>';
							text +=
							    '<a href="#"><object data="imgs/minus.png" width="12" height="12" title="Remove Condition" href="#" onclick="delCondition('+ inObject["id"] + ',' + intArray[j] + ',' + l.toString() +
							    ');"></object></a>';
			
							text += "<br>";
						}
						text += "<br>";

					}

				}

				text += "<br>";
			}
			break;	//break out of the loop right here
		}

	}


	text += "<dl>";
	return text;
}

//~ function selNodeLeftFrame(nodeId)
//~ {
	//~ //this function is deprecated 
//~ }

function selNodeData(selectedNode)
{
	//~ if (!(nodeId)) {return -1;}; //this makes sure we short circuit the function in its place right here                

	//~ selectedLeftPaneNode = nodeId; //assign this value right here 
	var selectBox = document.getElementById('nodeSelectionForm');

	selectedLeftPaneNode = selectBox.options[selectBox.selectedIndex].value;	//assign this value right here 
	//~ console.log(selectBox);
	//~ console.log(selectBox.options[selectBox.selectedIndex].value);
	//~ e.options[e.selectedIndex].value;
	if(selectedNode)
	{
		//this is empty for now
		selectedLeftPaneNode = selectedNode;
	} 
	updateLeftFrame();

}

function leftFrameListBox(inObj)
{
	if (!(inObj)) {
			var text =
	    '<label>Select Node</label> <select onchange="selNodeData()" id = "nodeSelectionForm"> <option value = "null"> Please Select a Node</option>';
		text += "</select><br><br>";
		text += 	'<label>No nodes... Please add one</label><br><a href="#"><object data="imgs/plus.png" width="12" height="12" title="Add a Node" href="#" onclick="showNodeAdd();"></object></a><br><br>';
		return text; //return this right here

	};			//this makes sure we short circuit the function in its place right here             

	var i = 0;

	var inObject;

	var text =
	    '<label>Select Node</label> <select onchange="selNodeData()" id = "nodeSelectionForm"> <option value = "null"> Please Select a Node</option>';

	//this below is the svgmain

	for (i = 0; i < inObj.length; i++) {
		//~ console.log(inObj[i].name);
		inObject = inObj[i];

		text +=
		    '<option value =' + inObject["id"] + '> ' +
		    inObject["name"] + '</option>';

		//~ nodeId = ;  //assigning the node id right here
		//~ nodeName = ;  //assigning the node name
		//~ 

	}

	text += "</select><br><br>";
	text +=
	    '<a href="#"><object data="imgs/plus.png" width="12" height="12" title="Add a Node" href="#" onclick="showNodeAdd();"></object></a><br><br>';

	return text;
}

function updateLeftFrame()
{

	//this right here is used to update the left frame..

	var leftFrame = document.getElementById('leftFrame');
	var leftFrameHeader = document.getElementById('leftFrameHeader');
	var leftFrameMiddle = document.getElementById('leftFrameMiddle');
	var leftFrameProportion =
	    document.getElementById('leftFrameProportion');

	leftFrameHeader.innerHTML = leftFrameListBox(mainJsonFile);
	// here we go right here  
	leftFrameMiddle.innerHTML =
	    nodeInfoToLeftFrame(mainJsonFile, selectedLeftPaneNode);

}

function displayActionsAndCondition(selectedVar)
{

	//display actions and conditions
	if (!(selectedVar == null)) {
		var topText = null;
		var bottomText = null;
		var menuActiveText = null;
	} else {
		return "<p> an error has occured selecting an action <p>";
	}

}

function returnJsonCrealObjects(jsonVar)
{
	//this function will parse the json object

	return JSON.parse(jsonVar);	//this is not good right here  
}

//~ var closeLeftFrame = false; 
//~ var closeRightFrame = false; 
//~ var closeMiddleFrame = false; 
//~ 

function toggleRightFrame()
{

	var frame = document.getElementById('rightFrame');
	if (frame) {
		if (frame.style.display == "none") {
			frame.style.display = "block";

		} else {
			frame.style.display = "none";

		}

	}
}

function toggleMiddleFrame()
{

	var frame = document.getElementById('middleFrame');
	var graphMiddleToggle = document.getElementById('middleGraphMenu');

	if (frame && graphMiddleToggle) {
		if (!(frame.style.display == "none")) {
			frame.style.display = "none";
			graphMiddleToggle.style.display = "block";
		} else {
			frame.style.display = "block";
			graphMiddleToggle.style.display = "none";
		}

	}

}

function toggleLeftFrame()
{

	var frame = document.getElementById('leftFrame');
	if (frame) {
		if (frame.style.display == "none") {
			frame.style.display = "block";

		} else {
			frame.style.display = "none";

		}

	}
}

function hideRightFrame()
{
	closeRightFrame = true;

	var frame = document.getElementById('rightFrame');
	if (frame) {
		if (closeRightFrame) {
			frame.style.display = "none";

		} else {
			frame.style.display = "block";

		}

	}
}

function showRightFrame()
{
	closeRightFrame = false;

	var frame = document.getElementById('rightFrame');
	if (frame) {
		if (frame.style.display == "none") {
			frame.style.display = "block";

		} else {
			frame.style.display = "none";

		}

	}
}



function addNode()
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return; 
	}
	var stringValue = document.getElementById('nodeNameTxtBox');
	if (stringValue) {
		var nodeTemplate = {	//this is the node template 

 "id":			nodeCount.toString(),
 "name":		stringValue.value,
 "synonyms":		" ",
 "image":		" ",
 "comment":		" ",
 "properties":		{}
			,
 "action list":	{}
		};
		if (!(mainJsonFile))
		{
			mainJsonFile = [];
		}
		mainJsonFile.push(nodeTemplate);	//adding the node here 
		nodeCount++;	//make sure you increase the node count right here when adding a new node
		selectRightFrame("close");
		//~ writeSvgObjInSpace();
		
		//~ mainSvgGraph.addNode(nodeTemplate["id"],parseInt(nodeTemplate["id"]),nodeTemplate['name']);
		updateLeftFrame();
		
	}

	//~ confirm("Are You Sure You Want to Delete this Property?");

}


//below are methods to modify the nodes 

function addActionList(selectedNode)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}
	if (!(selectedNode)) {
		return " ";
	}			// bad
	
	inObj = mainJsonFile;
	
	var  i, j, k;
	i = j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;
	
	
	var actionListProtoType = {"actions": [],
							  "conditions": [] };
	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];

		if (internalObject["id"] == selectedNode) {
			
			intActionLists = internalObject["action list"];  //internal action lists
			
			//~ refreshSvgSpace();	//this deletes everything and then adds shit
			//~ writeSvgObjInSpace();	//write to the space
			intActionLists[actionListCount.toString()] = actionListProtoType;
			updateLeftFrame();
			actionListCount++; 
			//console.log(intActionLists); 
			return true;	//everything is good right here 
		}

	}
	//TEMPLATE BELOW
	//~ var intActionLists;
	//~ intActionLists = inObj["action list"];
	//~ intActionLists[actionListCount.toString()] = " ";
	//~ console.log(intActionLists); 
	//append the structure object.  
	//~ inObj.appendChild(actionEncapsulationTemplate);

	return true;

}


function modCondition(selectedNode, actionListId, conditionIndex)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return "demo";
	}
	
		if (!(confirm("Are You Sure You Want to Mod this Condition?"))) 
		{
			return false;
		}


	var selectedConditionType = document.getElementById('selectedConditionType');
	var selectedConditionValue = document.getElementById('selectedConditionValue');
	var selectedConditionField = document.getElementById('selectedConditionField');


	

		updateLeftFrame();


}

function modProperty(selectedNode, propertyId)
{
		if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return "demo";
	}

		if (!(confirm("Are You Sure You Want to Mod this Property?"))) 
		
		{
			return false;
		}
	

		 var propName = document.getElementById("propNameTxtBox"); 
		 var propValue = document.getElementById("propValueTxtBox"); 
	
	
	inObj = mainJsonFile;

	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;
	var cachedNode; 
	
	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];
		//~ console.log(internalObject);
		if (internalObject["id"] == selectedNode) {	
				
		console.log(selectedNode);
		 cachedNode = internalObject["properties"]; 
		//~ console.log(cachedNode);
		//~ console.log(propertyId);
		//~ console.log(propertyId);
	     if(cachedNode[propertyId])
        {
               //~ console.log(cachedNode[propertyId]);
               
               
               cachedNode[propertyId]["name"] = propName.value; 
                
               cachedNode[propertyId]["value"] = propValue.value; 
              
               updateLeftFrame(); 
               
               return true; 
        } 	 
		else
		{
				console.log("an error occured when trying to delete this property");
				return false; 
		}
			

			
		}
	}
	

		
	//this is not needed anymore in this function... -Randy-Pull..
		//~ updateLeftFrame();
		//~ writeSvgObjInSpace();
}



//This function is deprecated.. 

/*
function modActionList(selectedNode, actionListId)
{
	//this isn't needed
		if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return "demo";
	}


	
	//~ confirm("Are You Sure You Want to Delete this Property?");

}
*/




function modAction(selectedNode, actionID, conditionIndex)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return "demo";
	}

	if (!(confirm("Are You Sure You Want to Mod this Action?"))) {
		return false;
	}
	
	if (!(selectedNode || actionID || conditionIndex))
	{
		return false;
	}
	
	var	actionType = document.getElementById("selectedActionType");
	var	targetValue = document.getElementById("selectedActionValue");
	var	targetId = document.getElementById("selectedPropId");


	if (targetId && targetValue && actionType)
	{
		
		
	}
	else
	{
		return false; //make sure this returns false right here 
	}
	

	updateLeftFrame();
	//~ writeSvgObjInSpace();
	return true; 
	
}


function modNode(selectedNode)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}

	if (!(selectedNode)) {
		return " ";
	}
	//everything is good right here 

	var i = 0;
	var j, k;
	j = k = 0;
	var internalObject;

	var textBox = document.getElementById('nodeNameTxtBox')

	if (!(confirm("Are You Sure You Want to Mod this Node?"))) {
		return false;
	}

	    if (textBox) {
		for (i = 0; i < mainJsonFile.length; i++) {

			internalObject = mainJsonFile[i];

			if (internalObject["id"] == selectedNode) {

				internalObject["name"] = textBox.value;
				updateLeftFrame();

				//~ writeSvgObjInSpace();
				selectRightFrame("close");
				return true;	//everything is good right here 
			}

		}
	}

}

function delCondition(selectedNode, actionListId, conditionIndex)
{

	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}


	if (!(confirm(" Are You Sure You Want to Delete this Condition? "))) {
		return " ";	//do something right here    


			if (!(selectedNode || actionListId || conditionIndex))
			{
				console.log("bad");
				return false; 
			}

	}


	inObj = mainJsonFile;
	//~ console.log(inObj);
			
	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;
	var cachedNode; 
	var cachedArray; 
	var cachedCondition; 
	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];
		//~ console.log(internalObject);
		if (internalObject["id"] == selectedNode) {	
				
		//~ console.log(selectedNode);
		 //~ cachedNode = internalObject["properties"]; 
		//~ console.log(cachedNode);
		//~ console.log(propertyId);

		cachedNode = internalObject["action list"]; 
		//~ console.log(cachedNode);
			//		 
			if (cachedNode[actionListId]) 
			{
				cachedArray = cachedNode[actionListId]; 					

				cachedCondition = cachedArray["conditions"]; 
				//if (cachedCondition)

				if (cachedCondition[conditionIndex])
				{


					console.log(cachedCondition[conditionIndex]);
					cachedCondition.splice(conditionIndex,1); 
					updateLeftFrame();
					return true; 
				}
		}
	
	}
}
	return false; 

}

function delActionList(selectedNode, actionListId)
{

	//~ if (!(inObj || actionListId)) {
		//~ return " ";
	//~ }			// everything wasn't good, short circuit

	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return "demo";
	}

	if (!(confirm(" Are You Sure You Want to Delete this Action List? "))) {
		return false;	//do something right here    

	}
	inObj = mainJsonFile;

			
	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;
	var cachedNode; 
	
	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];
		//~ console.log(internalObject);
		if (internalObject["id"] == selectedNode) {	

				cachedNode = internalObject["action list"]; 

				if (cachedNode[actionListId])
				{

					   console.log(cachedNode[actionListId]);
		               delete cachedNode[actionListId]; //I can't believe this is so fucking easy...
		               updateLeftFrame(); 
		               return true;

					

				}
				else
				{	
					console.log("Could not properly delete this action list ");

					return false; 
				}
		//~ console.log(selectedNode);
		 //~ cachedNode = internalObject["properties"]; 
		//~ console.log(cachedNode);
		//~ console.log(propertyId);
		 //this is what we are doing right hered 

//		 actionListId


		 /*
			if (cachedNode == propertyId) 
			{
				
				
				
					for (k = 0; k < cachedNode.length; k++)
					{
						//~ console.log(cachedNode); 
								if (true)
								{
									updateLeftFrame(); //make sure to update the left fram right here
									return true; 
								}
						
					}
			

			}
			*/
		}
	}
	//~ updateLeftFrame(); 
	return false; 
}

function delAction(selectedNode, actionListId, actionIndex)
{

	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}

		if (!(confirm(" Are You Sure You Want to Delete this Action List? "))) {
		return " ";	//do something right here    

	}
	inObj = mainJsonFile;
	//~ console.log(inObj);
			
	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;
	var cachedNode; 
	var cachedArray;
	var cachedActions; 
	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];
		//~ console.log(internalObject);
		if (internalObject["id"] == selectedNode) {	
				
		//~ console.log(selectedNode);
		 	cachedNode = internalObject["action list"]; 
			console.log(cachedNode);
			//		 
			//cachedActions = cachedNode["actions"]; 

			if (cachedNode[actionListId]) 
			{
				cachedActions = cachedNode[actionListId]["actions"];	
				cachedArray = cachedNode[actionListId]; 					
				if (cachedActions[actionIndex])
				{

					cachedActions.splice(actionIndex, 1);
					   updateLeftFrame(); 
		               return true;
			
				}
					console.log(cachedActions);



					if (cachedArray[actionIndex])
					{

						console.log(cachedArray[actionIndex]);

					}
					/*
					for (k = 0; k < cachedNode.length; k++)
					{
						//~ console.log(cachedNode); 
								if (true)
								{
									updateLeftFrame(); //make sure to update the left fram right here
									return true; 
								}
						
					}
					*/

			}
			else
			{

				console.log("An error happened while trying to delete this given action");
			}
			
		}
	}
	//~ updateLeftFrame(); 
	//~ writeSvgObjInSpace();
	return false; 
}

function delNode(selectedNode)
{
	 if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return;
	}
	inObj = mainJsonFile;
	if (!
	    (confirm("Are You Sure You Want to Delete this Node?") )) {
		return " ";
	}
	
	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;
	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];

		if (internalObject["id"] == selectedNode) {
			nodeSvgString = "svg_" + internalObject["id"];
			removalIndex = i;
			inObj.splice(removalIndex, 1);
			selectRightFrame("close");

			
			//~ writeSvgObjInSpace();	//write to the space
			updateLeftFrame();
			return true;	//everything is good right here 
		}

	}

	//~ var frame = document.getElementById('nodeNameTxtBox');        
}

function delProperty(selectedNode, propertyId)
{
	if (demoVar)
	{
			alert("This is a demo of our simulation.\nYou will not be able to edit anything =)"); //default
			return true;
	}
	
	if (!(selectedNode && propertyId))
	{
			return false; 
	}

	if (!
	    (confirm("Are You Sure You Want to Delete this Property?") )) {
		return false;
	}


	inObj = mainJsonFile;
	//~ console.log(inObj);
	var i = 0;
	var j, k;
	j = k = 0;

	var removalIndex;
	var internalObject;
	var intProperties;
	var intActionLists;
	var inObject;
	var inKeys;
	var intActionKeys;
	var intConditionKeys;
	var intArray;
	var nodeSvgString;
	var cachedNode; 
	
	for (i = 0; i < inObj.length; i++) {

		internalObject = inObj[i];
		//~ console.log(internalObject);
		if (internalObject["id"] == selectedNode) {	
				
		console.log(selectedNode);
		 cachedNode = internalObject["properties"]; 
		//~ console.log(cachedNode);
		//~ console.log(propertyId);
		//~ console.log(propertyId);
	     if(cachedNode[propertyId])
        {
               console.log(cachedNode[propertyId]);
               delete cachedNode[propertyId]; //I can't believe this is so fucking easy...
               updateLeftFrame(); 
               //~ mainSvgGraph.removeNode(propertyId);
               return true; 
        } 	 
		 else
			{
				console.log("an error occured when trying to delete this property");
				return false; 
			}
			

			
		}
	}
	

//~ writeSvgObjInSpace();

}

function loadFileToJsonObject(fileObject)
{

	if (!(fileObject)) {
		return -1;
	}

	var text = fileObject.value();
	//return the parsed json text into a place that we can further take these things 
	return JSON.parse(text);

}

function showDownloadButton()
{

	var frame = document.getElementById('fileOpenLink');
	if (frame) {
		if (frame.style.display == "none") {
			frame.style.display = "block";

		} else {
			frame.style.display = "none";

		}

	}

}




function makeSureThisThingIsGood()
{
	var  frame = document.getElementById('this'); 
	
	
	if (!(frame))
	{
		return false; //this means that we are going out of the demo scene....
		
	}
} 



function myGraph(el) {

// Add and remove elements on the graph object
this.addNode = function (id,color,name) {
    nodes.push({"id":id,"color":color,"name":name});
    update();
};

this.removeNode = function (id) {
    var i = 0;
    var n = findNode(id);
    while (i < links.length) {
        if ((links[i]['source'] == n)||(links[i]['target'] == n))
        {
            links.splice(i,1);
        }
        else i++;
    }
    nodes.splice(findNodeIndex(id),1);
    update();
};

this.removeLink = function (source,target){
    for(var i=0;i<links.length;i++)
    {
        if(links[i].source.id == source && links[i].target.id == target)
        {
            links.splice(i,1);
            break;
        }
    }
    update();
};

this.removeallLinks = function(){
    links.splice(0,links.length);
    update();
};

this.removeAllNodes = function(){
    nodes.splice(0,links.length);
    update();
};

this.addLink = function (source, target, value) {
    links.push({"source":findNode(source),"target":findNode(target),"value":value});
    update();
};

var findNode = function(id) {
    for (var i in nodes) {
        if (nodes[i]["id"] === id) return nodes[i];};
};

var findNodeIndex = function(id) {
    for (var i=0;i<nodes.length;i++) {
        if (nodes[i].id==id){
            return i;
        }
        };
};

// set up the D3 visualisation in the specified element
var w = 1280 ,
    h = 720 ;
    var width =w, height = h;
var vis = d3.select(el)
    .append("svg:svg")
    .attr("width", w)
    .attr("height", h)
    .attr("id","svg")
    .attr("pointer-events", "all")
    .attr("viewBox","0 0 "+w+" "+h)
    .attr("perserveAspectRatio","xMinYMid")
    .append('svg:g');

var force  = d3.layout.force().charge(-120).linkDistance(30).size([width, height]);
var color = d3.scale.category20();
var nodes = force.nodes(),
    links = force.links();

var update = function () {
      var link = vis.selectAll("line")
        .data(links, function(d) {
            return d.source.id + "-" + d.target.id; 
            });

    link.enter().append("line")
        .attr("id",function(d){return d.source.id + "-" + d.target.id;})
        .attr("class","link");
    link.append("title")
    .text(function(d){
        return d.value;
    });
    link.exit().remove();

    var node = vis.selectAll("g.node")
        .data(nodes, function(d) { 
            return d.id;});

    var nodeEnter = node.enter().append("g")
        .attr("class", "node")
        .style("fill", function(d) { return color(d.color); })
        .call(force.drag);

    nodeEnter.append("svg:circle")
    .attr("class", "node")
    .attr("r", 7)
    .attr("id",function(d) { return "Node;"+d.id;})
    .attr("class","nodeStrokeClass");

    nodeEnter.append("text")
      .attr("font-size", "20px")
      .attr("fill", "#000000")
		.attr("font-family", "sans-serif")
		.text( function(d){return d.name;});

    node.exit().remove();
    force.on("tick", function() {

        node.attr("transform", function(d) { return "translate(" + d.x + "," + d.y         + ")"; });

        link.attr("x1", function(d) { return d.source.x; })
          .attr("y1", function(d) { return d.source.y; })
          .attr("x2", function(d) { return d.target.x; })
          .attr("y2", function(d) { return d.target.y; });
    });

    // Restart the force layout.
    force
    .gravity(.05)
    .distance(50)
    .linkDistance( 50 )
    .size([w, h])
    .start();
};


// Make it all go
update();
}

function drawGraph()
{
graph = new myGraph("#svgdiv");
graph.addNode('A',3,"fff");
graph.addNode('B',3,"fff");
graph.addNode('C',4,"dddd");
graph.addLink('A','B','10');
//~ graph.addLink('A','C','8');
//~ graph.addLink('B','C','15');
}


			

					
			
 //on load
 
 function creaInit()
{
	mainSvgGraph = new myGraph(".middleFrame");
	nodeCount = actionListCount = propertyCount = 1;
	loadEnvironment(mainJsonFile);
	hideRightFrame();
	graphSimSwitchHeader("vis");
	updateLeftFrame();

};

 
window.onload = creaInit;

//this is the end of the script right here 
