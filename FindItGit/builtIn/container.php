<!DOCTYPE HTML>
<html>
<head>
	<style type="text/css">
		@import "../style.css"
	</style>
	<script src="../jquery-1.8.2.min.js"></script>
	<script>
	$(document).ready(function() {
		$('#htmlForm').ajaxForm({ 
		        // target identifies the element(s) to update with the server response 
		        target: '#loader', 
		 
		        // success identifies the function to invoke when the server response 
		        // has been received; here we apply a fade-in effect to the new content 
		        success: function() { 
		            	$('#resultados').fadeIn('slow'); 
			        } 
			    });
	    $('#resultados').html('<p><img src="../imagens/ajax-loader.gif" width="220" height="19" /></p>');
	    $('#resultados').load("comparador.php");
 	});
	</script>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta http-equiv="Content-Language" content="en" />
	<meta name="GENERATOR" content="PHPEclipse 1.2.0" />
</head>
<body>
	<div id="resultados">
		oiiiiiiiiiii		
	</div>
</body>
</html>