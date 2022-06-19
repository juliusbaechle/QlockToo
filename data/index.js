function initialize() {
	initializeSpecials('%possible_specials%');
	updateUtcLabel();
	setupEventSource();
}

function initializeSpecials(specialJson) {
	try {
		specials = JSON.parse(specialJson);
		if(specials.length == 0)
			document.getElementById("specials").style.display = "none";
		addSpecials(specials);
	} catch {
		document.getElementById("specials").style.display = "none";
	}
}

function addSpecials(specials) {
	addSpecial("");
	for (let special of specials)
		addSpecial(special);
	document.getElementById("special").value = "%special%";
}

function addSpecial(special) {
	var opt = document.createElement('option');
    opt.value = special;
    opt.innerHTML = special;
    document.getElementById("special").appendChild(opt);
}

function updateUtcLabel() {
	value = document.getElementById("utc_offset").value;
	var str = "Zeitzone: " + (value > 0 ? "+" : "") + value + "h";
	document.getElementById("headerTimeZone").innerHTML = str;
}

function setupEventSource() {
	var source = new EventSource('/events');
	source.addEventListener('auto_brightness', function(e) { setValue('auto_brightness', e.data) }, false);
	source.addEventListener('foreground_color', function(e) { setValue('foreground_color', e.data) }, false);
	source.addEventListener('background_color', function(e) { setValue('background_color', e.data) }, false);
	source.addEventListener('startup_time', function(e) { setValue('startup_time', e.data) }, false);
	source.addEventListener('shutdown_time', function(e) { setValue('shutdown_time', e.data) }, false);
	source.addEventListener('utc_offset', function(e) { setValue('utc_offset', e.data); updateUtcLabel(); }, false);
	source.addEventListener('special', function(e) { setValue('special', e.data) }, false);
}

function setValue(variable, value) {
	console.log(variable, value);
	element = document.getElementById(variable);
	element.value = value;
}

function sendVariable(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/" + element.id + "?value=" + encodeURIComponent(element.value), true);
	xhr.send();
}