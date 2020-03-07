//-----------------------------------------------
//Originally published by Mogsdad@Stackoverflow
//Modified for The OPEnS Lab
//Modified by Thomas DeBell
//Modified by Ronnie Conlon
//-----------------------------------------------
/*


GET request query:


https://script.google.com/macros/s/<gscript id>/exec?celData=data_here
----------------------------------------------------------------------


GScript, PushingBox and Arduino/ESP8266 Variables in order:


IDtag
half
full

----------------------------------------------------
*/


function doGet(e) { 
  Logger.log( JSON.stringify(e) );  // view parameters


  var result = 'Ok'; // assume success


  if (e.parameter == undefined) {
    result = 'No Parameters';
  }
  else {
    var id = '1Qyy25yesqFlnQmXB5tJPd1JoPqWuW3Znv48zgeDISZI';//specific to the spreadsheet you are working on. this is id is found     //directly after "docs.google.com/spreadsheetURL/d" in the URL. 
   
    var sheet = SpreadsheetApp.openById(id).getActiveSheet();
    var newRow = sheet.getLastRow() + 1;
    var lc = sheet.getLastColumn();
    var rowData = [];
    var waktu = new Date();
    
    rowData[0] = waktu.toLocaleDateString() + " " + waktu.toLocaleTimeString(); // Timestamp in column A
    rowData[1] = Date.now();
    
    for (var param in e.parameter) {
      Logger.log('In for loop, param='+param);
      var value = stripQuotes(e.parameter[param]);
      //Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'half':
          rowData[2] = value;
          break;
        case 'full':
          rowData[3] = value;
          break;
        default:
          result = "unsupported parameter";
      }
    }
    Logger.log(JSON.stringify(rowData));

    // Write new row below
    var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
    newRange.setValues([rowData]);
    
    // Sort document in descending order by the ID
    var rngs = sheet.getRange(2, 1, newRow, lc);
    rngs.sort({column: 2, ascending: false});
  }
  
  
  // Return result of operation
  return ContentService.createTextOutput(result);
}


/*
*  Remove leading and trailing single or double quotes
*/
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}