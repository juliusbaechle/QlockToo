function onActiveChanged(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/active?value=" + element.checked, true);
	xhr.send();
}

function initialize() {
	var specials = JSON.parse('%POSSIBLE_SPECIALS%');
	if(specials.length == 0) return;
	
	var select = document.createElement("select");
	select.id = "specials";

	var optionStr = '<option value=""> - </option>';
	for (let special of specials)
		optionStr += '<option value="' + special + '">' + special + '</option>';				
	select.innerHTML = optionStr;
	
	select.onchange = function() {
		var xhr = new XMLHttpRequest();
		xhr.open("PUT", "/special?value=" + select.value, true);
		xhr.send();
	}
	
	document.body.appendChild(select);
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

function updateUtcOffset(element) {
	document.getElementById("textUtcOffset").innerHTML = element.value + " h";
}

function sendUtcOffset(element) {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/utc_offset?value=" + encodeURIComponent(element.value), true);
	xhr.send();
}

class Color {
	constructor(r, g, b) {
		this.r = Math.round(r);
		this.g = Math.round(g);
		this.b = Math.round(b);
	}

	static fromHsv(h, s, v) {
		var main = (v * s) / 255;
		var blending = Math.round(main * (1 - Math.abs((h/60) % 2 - 1)));
		var white = v - main;

		var c;
		if(0 <= h && h < 60)
			c = new Color(main, blending, 0);
		if(60 <= h && h < 120)
			c = new Color(blending, main, 0);
		if(120 <= h && h < 180)
			c = new Color(0, main, blending);
		if(180 <= h && h < 240)
			c = new Color(0, blending, main);
		if(240 <= h && h < 300)
			c = new Color(blending, 0, main);
		if(300 <= h && h < 360)
			c = new Color(main, 0, blending);
		
		c.r += white;
		c.g += white;
		c.b += white;
		return c;
	}
	
	toString() {
		var str = "#";
		str += this.r.toString(16).padStart(2, '0');
		str += this.g.toString(16).padStart(2, '0');
		str += this.b.toString(16).padStart(2, '0');
		return str;
	}
}

function currentForegroundColor() {
	var c = Color.fromHsv(
		Math.round(document.getElementById("sldForegroundHue").value),
		Math.round(document.getElementById("sldForegroundSaturation").value),
		Math.round(document.getElementById("sldForegroundValue").value)
	);
	return c.toString();
}

function updateForegroundColor() {
	document.getElementById("btnForegroundColor").style.background = currentForegroundColor();
}

function sendForegroundColor() {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/foreground_color?value=" + encodeURIComponent(currentForegroundColor()), true);
	xhr.send();
}

function currentBackgroundColor() {
	var c = Color.fromHsv(
		Math.round(document.getElementById("sldBackgroundHue").value),
		Math.round(document.getElementById("sldBackgroundSaturation").value),
		Math.round(document.getElementById("sldBackgroundValue").value)
	);
	return c.toString();
}

function updateBackgroundColor() {
	document.getElementById("btnBackgroundColor").style.background = currentBackgroundColor();
}

function sendBackgroundColor() {
	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/background_color?value=" + encodeURIComponent(currentBackgroundColor()), true);
	xhr.send();
}

function toggleAutoBrightness(element) {
	var inpValue = document.getElementById("foregroundValueSpan");
	var sldValue = document.getElementById("sldForegroundValue");
	
	if(element.checked) {
		document.getElementById("sldForegroundValue").value = "255";
		inpValue.style.display = "none";
		sldValue.style.display = "none";
		updateForegroundColor();
	} else{
		inpValue.style.display = "block";
		sldValue.style.display = "block";
	}

	var xhr = new XMLHttpRequest();
	xhr.open("PUT", "/auto_brightness?value=" + element.checked, true);
	xhr.send();
}