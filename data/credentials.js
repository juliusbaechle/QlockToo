const togglePassword = document.querySelector("#togglePassword");
const password = document.querySelector("#password");
const body = document.querySelector("body");
var timerId;

togglePassword.addEventListener("mouseenter", function( event ) {	
	password.setAttribute("type", "text");
});

togglePassword.addEventListener("mouseleave", function( event ) {	
	password.setAttribute("type", "password");
});

function onTimeout() {
	document.body.style.background = "#bdffc0";
	window.clearInterval(timerId);
}

timerId = window.setInterval(function() {
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/ping", true);
	xhr.timeout = 1900;
	xhr.ontimeout = onTimeout;
	xhr.send();
}, 2000);