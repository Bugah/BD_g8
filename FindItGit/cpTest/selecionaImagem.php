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
		$(document).ready(function() {
			$("#showRes").click(function() {
				alert("pegou!");
				$("#resultado").load("resultadoImg.php");
			});
			
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
			$("#upload").click(function() {
				var x = $('#file').val();
				$("#loader").load("comparador.php?"+x+" #tst");
				alert("oi");
				alert($('#file').val());
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

<h1 style="color:#BB8855;">Busca por imagens semelhantes</h1>

<!-- Formulário para receber aquisições !-->
<form id="htmlForm" class="center" action="builtIn/comparador.php" method="post" enctype="multipart/form-data">
	<p>
	<label for="file">Coloque o arquivo aqui:</label>
	<input type="file" id="file" name="file" size="50" maxlength="100000" accept="image/*" onchange="confereImg(this)"/>
	<input type="hidden" name="busca" id="busca" value="busca"/>
	<input type="hidden" name="wow" id="wow" value="haha"/>
	
	<input type="submit" id="submissao" value="Buscar"/>
	</p>
</form>

<div id="loader">
</div>

</body>
</html>
