function addSpecial(special) {
	var opt = document.createElement('option');
    opt.value = special;
    opt.innerHTML = special;
    document.getElementById("specialSelect").appendChild(opt);
}

function setSpecials(specials) {
	if(specials.length == 0)
		return document.getElementById("specialSelect").style.display = "none";

	addSpecial("");
	for (let special of specials)
		addSpecial(special);
}

function updateUtcOffset(element) {
	var str = "Zeitzone: " + (element.value > 0 ? "+" : "") + element.value + "h";
	document.getElementById("headerTimeZone").innerHTML = str;
}

function initialize() {
	setSpecials(JSON.parse('%POSSIBLE_SPECIALS%'));
	updateUtcOffset(document.getElementById("sldUtcOffset"));
}


function sendAdaptiveLuminosity(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/auto_brightness?value=" + element.checked, true);
	xhr.send();
}

function sendForegroundColor(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/foreground_color?value=" + encodeURIComponent(element.value), true);
	xhr.send();
}

function sendBackgroundColor(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/background_color?value=" + encodeURIComponent(element.value), true);
	xhr.send();
}

function sendShutdownTime(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/shutdown_time?value=" + element.value, true);
	xhr.send();
}

function sendStartupTime(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/startup_time?value=" + element.value, true);
	xhr.send();
}

function sendUtcOffset(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/utc_offset?value=" + encodeURIComponent(element.value), true);
	xhr.send();
}

function sendSpecial(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/special?value=" + element.value, true);
	xhr.send();
}