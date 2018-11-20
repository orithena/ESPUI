const char JS_CONTROLS[] PROGMEM = R"=====(
const UI_TITEL=0;const UI_LABEL=1;const UPDATE_LABEL=6;const UI_BUTTON=2;const UI_SWITCHER=3;const UPDATE_SWITCHER=7;const UI_PAD=4;const UI_CPAD=5;const UI_SLIDER=8;const UPDATE_SLIDER=9;const UI_NUMBER=10;const UPDATE_NUMBER=11;const UI_TEXT_INPUT=12;const UPDATE_TEXT_INPUT=13;const UI_GRAPH=14;const CLEAR_GRAPH=15;const ADD_GRAPH_POINT=16;const FOR=0;const BACK=1;const LEFT=2;const RIGHT=3;const CENTER=4;const C_TURQUOISE=0;const C_EMERALD=1;const C_PETERRIVER=2;const C_WETASPHALT=3;const C_SUNFLOWER=4;const C_CARROT=5;const C_ALIZARIN=6;const C_NONE=7;function colorClass(colorId){colorId=Number(colorId);switch(colorId){case C_TURQUOISE:return"turquoise";break;case C_EMERALD:return"emerald";break;case C_PETERRIVER:return"peterriver";break;case C_WETASPHALT:return"wetasphalt";break;case C_SUNFLOWER:return"sunflower";break;case C_CARROT:return"carrot"
break;case C_ALIZARIN:return"alizarin"
break;case C_NONE:return""
break;default:return"";}}
var websock;var websockConnected=false;function restart(){$(document).add('*').off();$("#row").html("");websock.close();start();}
function conStatusError(){websockConnected=false;$("#conStatus").removeClass("color-green");$("#conStatus").addClass("color-red");$("#conStatus").html("Error / No Connection &#8635;");$("#conStatus").off();$("#conStatus").on({'click':restart});}
function handleVisibilityChange(){if(!websockConnected&&!document.hidden){restart();}}
function start(){document.addEventListener("visibilitychange",handleVisibilityChange,false);websock=new WebSocket('ws://'+window.location.hostname+'/ws');websock.onopen=function(evt){console.log('websock open');$("#conStatus").addClass("color-green");$("#conStatus").text("Connected");websockConnected=true;};websock.onclose=function(evt){console.log('websock close');conStatusError();};websock.onerror=function(evt){console.log(evt);conStatusError();};websock.onmessage=function(evt){console.log(evt);var data=JSON.parse(evt.data);var e=document.body;var center="";switch(data.type){case UI_TITEL:document.title=data.label;$('#mainHeader').html(data.label);break;case UI_LABEL:$('#row').append("<div class='two columns card tcenter "+colorClass(data.color)+"'><h5 id='"+data.id+"'>"+data.label+"</h5><hr /><span id='l"+data.id+"' class='label label-wrap'>"+data.value+"</span></div>");break;case UI_BUTTON:$('#row').append("<div class='one columns card tcenter "+colorClass(data.color)+"'><h5>"+data.label+"</h5><hr/><button onmousedown='buttonclick("+data.id+", true)' onmouseup='buttonclick("+data.id+", false)' id='"+data.id+"'>"+data.value+"</button></div>");$('#'+data.id).on({'touchstart':function(e){e.preventDefault();buttonclick(data.id,true)}});$('#'+data.id).on({'touchend':function(e){e.preventDefault();buttonclick(data.id,false)}});break;case UI_SWITCHER:var label="<label id='sl"+data.id+"' class='switch checked'>";var input="<div class='in'><input type='checkbox' id='s"+data.id+"' onClick='switcher("+data.id+",null)' checked></div>";if(data.value=="0"){label="<label id='sl"+data.id+"' class='switch'>";input="<div class='in'><input type='checkbox' id='s"+data.id+"' onClick='switcher("+data.id+",null)' ></div>";}
$('#row').append("<div id='"+data.id+"' class='one columns card tcenter "+colorClass(data.color)+"'><h5>"+data.label+"</h5><hr/>"+
label+input+
"</label>"+
"</div>");break;case UI_CPAD:center="<a class='confirm' onmousedown='padclick(CENTER, "+data.id+", true)' onmouseup='padclick(CENTER, "+data.id+", false)' href='#' id='pc"+data.id+"'>OK</a>";case UI_PAD:$('#row').append("<div class='two columns card tcenter "+colorClass(data.color)+"'><h5>"+data.label+"</h5><hr/>"+
"<nav class='control'>"+
"<ul>"+
"<li><a onmousedown='padclick(FOR, "+data.id+", true)' onmouseup='padclick(FOR, "+data.id+", false)' href='#' id='pf"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(RIGHT, "+data.id+", true)' onmouseup='padclick(RIGHT, "+data.id+", false)' href='#' id='pr"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(LEFT, "+data.id+", true)' onmouseup='padclick(LEFT, "+data.id+", false)' href='#' id='pl"+data.id+"'>▲</a></li>"+
"<li><a onmousedown='padclick(BACK, "+data.id+", true)' onmouseup='padclick(BACK, "+data.id+", false)' href='#' id='pb"+data.id+"'>▲</a></li>"+
"</ul>"+
center+
"</nav>"+
"</div>");$('#pf'+data.id).on({'touchstart':function(e){e.preventDefault();padclick(FOR,data.id,true)}});$('#pf'+data.id).on({'touchend':function(e){e.preventDefault();padclick(FOR,data.id,false)}});$('#pl'+data.id).on({'touchstart':function(e){e.preventDefault();padclick(LEFT,data.id,true)}});$('#pl'+data.id).on({'touchend':function(e){e.preventDefault();padclick(LEFT,data.id,false)}});$('#pr'+data.id).on({'touchstart':function(e){e.preventDefault();padclick(RIGHT,data.id,true)}});$('#pr'+data.id).on({'touchend':function(e){e.preventDefault();padclick(RIGHT,data.id,false)}});$('#pb'+data.id).on({'touchstart':function(e){e.preventDefault();padclick(BACK,data.id,true)}});$('#pb'+data.id).on({'touchend':function(e){e.preventDefault();padclick(BACK,data.id,false)}});$('#pc'+data.id).on({'touchstart':function(e){e.preventDefault();padclick(CENTER,data.id,true)}});$('#pc'+data.id).on({'touchend':function(e){e.preventDefault();padclick(CENTER,data.id,false)}});break;case UPDATE_LABEL:$('#l'+data.id).html(data.value);break;case UPDATE_SWITCHER:if(data.value=="0")
switcher(data.id,0);else
switcher(data.id,1);break;case UI_SLIDER:$('#row').append("<div class='two columns card tcenter card-slider "+colorClass(data.color)+"'>"+
"<h5 id='"+data.id+"'>"+data.label+"</h5><hr />"+
"<div id='sl"+data.id+"' class='rkmd-slider slider-discrete slider-"+colorClass(data.color)+"'>"+
"<input type='range' min='0' max='100' value='"+data.value+"'>"+
"</div>"+
"</div>");$('#row').append("<script>"+
"rkmd_rangeSlider('#sl"+data.id+"');"+
"</script>");break;case UPDATE_SLIDER:slider_move($('#sl'+data.id),data.value,'100',false);break;case UI_NUMBER:$('#row').append("<div class='two columns card tcenter"+colorClass(data.color)+"'>"+
"<h5 id='"+data.id+"'>"+data.label+"</h5><hr />"+
"<input id='num"+data.id+"' type='number' value='"+data.value+"' onchange='numberchange("+data.id+")' />"+
"</div>");break;case UPDATE_NUMBER:$('#num'+data.id).val(data.value);break;case UI_TEXT_INPUT:$('#row').append("<div class='two columns card tcenter"+colorClass(data.color)+"'>"+
"<h5 id='"+data.id+"'>"+data.label+"</h5><hr />"+
"<input id='num"+data.id+"' type='number' value='"+data.value+"' onchange='numberchange("+data.id+")' />"+
"</div>");break;case UPDATE_TEXT_INPUT:$('#num'+data.id).val(data.value);break;default:console.error('Unknown type or event');break;}};}
function numberchange(number){var val=$('#num'+data.id).val();websock.send("nchange:"+number+":"+val);console.log(val);}
function buttonclick(number,isdown){if(isdown)websock.send("bdown:"+number);else websock.send("bup:"+number);}
function padclick(type,number,isdown){switch(type){case CENTER:if(isdown)websock.send("pcdown:"+number);else websock.send("pcup:"+number);break;case FOR:if(isdown)websock.send("pfdown:"+number);else websock.send("pfup:"+number);break;case BACK:if(isdown)websock.send("pbdown:"+number);else websock.send("pbup:"+number);break;case LEFT:if(isdown)websock.send("pldown:"+number);else websock.send("plup:"+number);break;case RIGHT:if(isdown)websock.send("prdown:"+number);else websock.send("prup:"+number);break;}}
function switcher(number,state){if(state==null){if($('#s'+number).is(':checked')){websock.send("sactive:"+number);$('#sl'+number).addClass('checked');}else{websock.send("sinactive:"+number);$('#sl'+number).removeClass('checked');}}else if(state==1){$('#sl'+number).addClass('checked');$('#sl'+number).prop("checked",true);}else if(state==0){$('#sl'+number).removeClass('checked');$('#sl'+number).prop("checked",false);}}
)=====";

const uint8_t JS_CONTROLS_GZIP[1997] PROGMEM = { 31,139,8,0,91,88,244,91,2,255,237,89,219,114,219,182,22,125,247,87,176,76,38,36,43,69,178,147,147,94,36,209,51,138,172,212,58,85,37,87,150,155,78,95,52,16,9,69,28,83,32,11,130,82,82,143,126,227,124,72,63,169,95,114,54,0,130,55,147,150,106,39,125,234,139,77,108,110,44,172,125,3,192,45,39,32,17,211,110,70,139,249,104,62,28,219,167,93,71,9,198,253,183,32,56,83,130,171,139,254,124,152,8,191,201,180,222,222,204,231,211,137,253,42,147,92,191,31,205,7,151,195,153,253,186,56,53,149,127,155,233,94,245,47,236,255,100,195,1,31,191,201,65,141,71,23,48,225,187,18,144,148,126,159,233,77,110,126,122,11,146,179,211,162,162,18,159,101,154,243,225,175,243,197,104,114,117,51,183,207,94,21,181,243,175,94,103,51,126,152,245,175,46,237,51,197,114,48,30,246,103,74,168,168,246,47,46,164,104,113,53,29,77,96,190,114,208,187,233,44,117,233,219,254,224,199,212,157,227,225,187,121,234,180,217,232,135,203,121,234,174,193,112,50,7,214,233,130,139,249,205,236,231,155,233,232,122,152,66,13,22,195,159,134,179,254,248,34,197,27,44,174,134,48,107,54,250,5,166,190,74,133,239,135,243,254,245,213,101,127,156,131,95,92,223,76,222,141,167,239,11,107,12,250,179,217,116,158,250,126,176,232,143,71,191,245,103,163,73,26,235,193,98,50,157,12,33,120,171,152,56,204,11,136,230,4,126,64,7,62,138,34,83,60,142,92,235,46,121,176,39,241,102,137,105,42,239,70,59,143,57,235,156,30,138,112,222,180,14,197,44,166,68,135,63,191,199,129,23,97,189,187,164,24,221,118,19,197,196,94,165,134,55,152,34,223,45,41,101,46,80,122,33,102,152,82,111,139,105,73,53,115,140,82,221,97,134,162,112,141,124,86,82,77,221,165,52,163,152,172,252,96,119,15,83,250,80,105,57,136,210,128,233,39,5,21,229,85,165,132,124,239,15,68,61,82,82,227,158,86,42,234,149,139,87,40,246,89,42,238,238,247,39,91,68,181,29,94,70,129,115,219,205,61,15,2,66,176,195,176,107,175,144,31,225,44,98,20,71,12,81,102,90,119,207,77,55,112,226,13,38,204,106,33,215,53,141,175,13,171,21,172,86,166,213,125,110,234,207,104,176,211,173,214,154,109,124,83,215,173,110,130,219,114,252,32,194,160,146,160,116,247,39,185,100,32,215,12,177,56,26,130,217,20,86,168,225,194,209,83,93,88,131,226,77,176,197,50,139,116,145,30,47,63,80,140,137,110,221,83,5,158,5,61,138,221,10,45,73,90,176,208,218,218,36,208,18,6,156,228,139,103,223,125,243,250,77,183,98,86,102,122,65,74,204,59,195,241,61,231,214,232,36,190,219,23,172,94,35,226,250,248,23,47,242,150,158,239,177,79,3,16,124,0,15,221,121,43,243,171,178,7,94,188,248,74,57,189,181,246,92,23,19,235,46,141,8,15,103,10,171,162,148,170,131,233,195,45,60,140,189,136,97,2,133,165,111,211,53,29,177,166,222,172,230,210,20,110,79,67,104,19,188,211,222,227,229,53,60,99,102,26,187,168,211,110,27,141,157,71,220,96,215,242,3,7,113,2,173,117,16,49,130,54,184,97,180,119,145,145,37,64,64,130,16,19,91,17,53,241,150,241,154,39,81,224,99,152,253,1,0,165,166,198,245,140,195,49,172,139,53,195,31,153,169,167,174,203,114,48,203,39,70,99,220,221,231,168,137,236,60,134,155,80,4,114,229,156,45,160,97,46,123,0,141,11,30,70,216,224,40,66,31,240,33,12,94,184,46,98,200,254,239,245,116,210,10,17,133,18,131,23,45,46,147,111,177,157,38,194,50,112,63,9,153,3,35,76,109,216,7,146,173,149,171,183,216,167,16,39,155,171,58,210,59,233,92,230,49,31,160,184,158,143,150,216,7,167,27,207,54,200,35,151,24,185,152,26,73,237,100,10,86,126,127,83,55,130,14,159,5,251,3,168,163,16,130,236,154,122,207,245,182,224,84,8,171,109,176,93,192,15,134,120,67,34,13,182,64,87,99,146,169,166,55,114,231,133,88,67,140,173,134,110,156,247,214,111,52,207,181,13,189,33,94,120,46,23,38,3,193,164,161,247,218,235,55,160,7,53,125,222,139,66,68,132,190,159,159,160,24,136,9,154,248,251,114,71,81,152,34,109,145,31,99,142,196,231,159,247,218,192,250,92,47,219,40,239,51,7,140,132,236,120,148,145,53,54,129,73,203,152,49,40,124,72,154,32,142,48,212,34,177,13,41,19,219,143,153,51,180,169,241,204,183,12,165,28,135,15,168,202,234,55,106,189,155,250,68,34,100,94,225,14,48,212,132,100,39,100,65,236,172,197,222,100,116,178,164,182,238,112,43,164,152,111,79,23,242,140,130,58,200,19,74,64,154,130,246,126,255,0,54,56,250,81,200,210,74,14,93,12,166,186,114,118,120,197,8,167,219,122,79,230,7,119,72,84,153,63,178,158,52,96,3,91,164,11,158,18,245,230,145,48,102,118,33,11,60,2,65,21,114,141,215,157,109,136,41,203,224,163,116,119,84,0,15,200,128,83,86,240,124,11,207,197,137,196,190,15,81,74,214,84,81,232,194,41,146,69,201,182,245,83,221,186,251,123,102,112,250,255,8,245,148,243,254,164,166,118,202,41,248,197,138,73,111,156,72,153,48,176,113,2,175,196,152,191,208,107,202,158,127,121,116,212,158,218,67,138,27,108,214,43,143,110,140,98,97,134,200,149,249,39,175,234,77,237,64,117,62,172,175,74,116,77,241,202,134,194,16,142,10,157,66,181,78,127,236,181,17,56,87,209,229,108,191,204,62,252,144,87,245,30,65,219,156,107,24,13,124,67,190,136,19,239,250,222,57,120,175,218,91,240,49,116,188,171,238,43,87,251,105,85,240,211,95,255,251,147,59,10,2,238,29,230,35,62,187,142,103,84,165,94,205,137,62,158,19,255,46,60,158,82,133,118,53,35,255,241,140,248,103,235,241,140,42,180,171,25,45,31,102,212,150,9,37,115,86,8,32,245,138,5,204,243,63,92,61,225,140,42,228,90,229,33,85,3,127,204,49,85,9,158,157,83,2,221,255,28,228,69,14,84,179,247,159,206,190,128,94,162,79,63,7,125,89,85,213,252,233,211,249,23,225,75,6,44,63,135,1,34,227,171,249,47,159,206,191,128,94,162,239,124,14,250,201,145,84,109,128,243,116,3,74,248,213,55,181,92,111,81,28,107,249,196,205,190,73,196,45,168,106,98,122,205,171,184,47,157,164,151,22,69,225,212,234,98,32,113,255,197,217,189,235,163,104,52,62,246,160,229,131,151,145,239,185,7,14,93,177,169,253,173,15,32,49,67,93,169,170,111,127,244,118,147,46,46,255,189,116,189,200,161,152,97,53,62,200,41,127,63,164,188,151,96,104,27,15,142,134,83,248,143,62,218,198,217,41,60,73,87,27,197,207,9,35,191,83,151,247,236,146,43,129,148,23,50,161,198,73,47,196,74,215,130,34,40,23,173,179,186,18,77,205,169,76,6,25,52,105,228,130,55,151,204,231,2,40,203,169,102,198,181,41,172,80,77,146,98,248,101,251,248,145,225,255,2,17,151,241,224,147,72,188,41,4,93,198,136,136,158,107,93,72,224,184,150,157,34,165,40,71,249,187,60,28,210,237,250,75,114,190,167,46,156,2,48,185,58,133,117,106,203,52,223,119,255,215,159,5,127,150,28,115,140,79,85,39,88,117,146,68,167,202,52,110,200,45,129,171,155,32,175,5,84,19,59,178,161,38,237,247,249,190,101,129,177,28,88,119,252,51,23,22,178,171,121,100,77,192,72,4,45,177,190,163,55,228,252,134,14,143,160,40,154,98,105,135,75,8,114,11,231,191,222,229,188,166,23,241,27,167,104,153,38,143,197,133,150,92,150,46,35,55,111,173,164,18,135,57,133,220,114,233,49,196,157,210,44,45,152,52,206,114,61,51,121,88,117,234,152,132,206,97,42,161,83,224,146,11,56,92,4,235,145,87,71,32,175,234,144,249,37,161,30,250,8,255,133,203,58,104,126,255,171,135,246,143,128,246,235,160,197,213,172,30,155,30,129,77,43,176,11,125,116,117,196,39,145,135,187,17,195,34,211,196,147,109,139,230,5,31,139,35,194,80,80,45,47,50,141,142,234,0,89,233,143,25,201,186,17,2,248,45,206,45,173,78,24,53,63,109,115,27,41,72,119,207,45,40,35,121,228,32,86,254,23,146,60,156,192,211,50,91,206,248,175,58,135,105,148,117,66,26,132,166,158,188,215,229,5,176,91,198,62,189,143,93,67,235,0,124,114,208,238,247,255,7,138,212,200,181,120,30,0,0 };
