<!-- Sistema de upload com possibilidade de troca de título feito em PHP. !-->
<?php 
require_once 'connect.php';
acionaTempo();
 ?>
<!DOCTYPE HTML>
<html xmlns="http://www.w3.org/1999/xhtml" lang="en_US" xml:lang="en_US">
<head>
<!-- Importando CSS para estilizar o documento !-->
	<style type="text/css">
		@import "style.css";
	</style>
	<script src="scripts/ajaxImageUploader/ajaximage/scripts/jquery.form.js"></script>
	<script>
			
			function confereImg(w,x) {
				if(w.value) {
					document.getElementById("submeter").disabled=false;
				}
			}
			
			function valida() {
				if(document.getElementById("file").value) {
					document.getElementById("submeter").disabled=false;
					document.getElementById("htmlForm").submit();
				}
				return false;
			}
			
		function loading() {
			// $('#loading').html('<p>owowo<img src="../imagens/ajax-loader.gif" width="220" height="19" /></p>');
			$('#loading').css("display","block");
		}
		$(document).ready(function() {
			
			$('#htmlForm').ajaxForm({ 
	        // target identifies the element(s) to update with the server response 
	        target: '#loader', 
	 
	        // success identifies the function to invoke when the server response 
	        // has been received; here we apply a fade-in effect to the new content 
	        success: function() { 
	        	
	            	$('#loader').fadeIn('slow'); 
		        } 
		    });
		    
			$("li").click(function() {
				$(this).css("border-style","inset");
			});
			
		});
	</script>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta http-equiv="Content-Language" content="pt-br" />
	<meta name="GENERATOR" content="PHPEclipse 1.2.0" />
	<title>FindIt</title>
</head>

<body>
<?php 
require_once 'menu.php';
// Mantém o tipo da busca
if (isset($_REQUEST['buscaTipo'])) {
	$_SESSION["tipo"] = $_REQUEST['buscaTipo'];
}
?>

<h1 style="color:#999955;text-shadow: #DDD 5px 5px 2px;text-transform: uppercase;">Busca por imagens semelhantes</h1>

<!-- Formulário para receber aquisições !-->
<form id="htmlForm" class="centerTxt" action="builtIn/comparador.php" method="post" enctype="multipart/form-data">
	<p>
	<label for="file">Coloque o arquivo aqui:</label>
	<input type="file" id="file" name="file" size="50" maxlength="100000" accept="image/*" onchange="confereImg(this)"/>
	<input type="hidden" name="busca" id="busca" value="busca"/>
	<input type="hidden" name="wow" id="wow" value="haha"/>
	
	<input type="submit" id="submeter" disabled="disabled" value="Buscar" onclick="loading();"/>
	</p>
</form>

<div id="loading" style="display: none;">
	<div class="center2">
		<h2>Aguarde, buscando imagens...&nbsp;<img class="centerTxt" src="imagens/ajax-loader.gif" width="220" height="19" /></h2>
		
		<img src="imagens/loading5.gif" height="400px" />
		
	</div>
</div>

<div id="loader">
</div>

</body>
</html>
