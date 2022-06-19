const togglePassword = document.querySelector("#togglePassword");
const password = document.querySelector("#password");

togglePassword.addEventListener("mouseenter", function( event ) {	
	password.setAttribute("type", "text");
});

togglePassword.addEventListener("mouseleave", function( event ) {	
	password.setAttribute("type", "password");
});

var source = new EventSource('/events');
source.addEventListener('error', function(e) {
	if (e.target.readyState != EventSource.OPEN) {
		console.log("events disconnected");
		document.body.style.background = "#bdffc0";
	}
}, false);
