const togglePassword = document.querySelector("#togglePassword");
const password = document.querySelector("#password");

togglePassword.addEventListener("mouseenter", function( event ) {	
	password.setAttribute("type", "text");
});

togglePassword.addEventListener("mouseleave", function( event ) {	
	password.setAttribute("type", "password");
});