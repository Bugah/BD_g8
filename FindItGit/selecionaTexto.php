<!-- Página de formulário para busca textual. !-->

<!DOCTYPE HTML"
	"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en_US" xml:lang="en_US">
<head>
<!-- Importando CSS para estilizar o documento !-->
	<style type="text/css">
		@import "style.css";
	</style>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta http-equiv="Content-Language" content="pt-br" />
	<meta name="GENERATOR" content="PHPEclipse 1.2.0" />
	<title>FindIt</title>
	
	<script>
			$(document).ready(function() {
				$(".desc").hide();
				$(".img").hover(function() {
					$(this).find("div").toggle(500);
				});
				
				$("li").click(function() {
					$(this).css("border-style","inset");
				});
				
			});
			
			function confereImg(w,x) {
				if(w.value) {
					document.getElementById("submeter").disabled=false;
				}
			}
			
			function valida() {
				if(document.getElementById("texto").value) {
					document.getElementById("submeter").disabled=false;
					document.getElementById("upForm").submit();
				}
			}
			
		</script>
</head>


<body>
<?php
require_once 'menu.html';
// Mantém o tipo da busca
if (isset($_REQUEST['buscaTipo'])) {
	$_SESSION["tipo"] = $_REQUEST['buscaTipo'];
}
?>

<h1>Busca via texto</h1>

<!-- Formulário para receber aquisições !-->
<form id="upForm" action="resultadoTxt.php" method="post" enctype="multipart/form-data">
	<p>
	<label for="texto">Insira as palavras-chave da imagem: </label> 
	<input type="text" class="text" name="texto" id="texto" value="" size="50" maxlength="50" autofocus="" onchange="confereImg(this)"/>
	
	<input id="submeter" type="button" value="Buscar" onclick="valida();" />
	</p>
</form>
<?php

?>

<!-- Música para relaxar! :o) !-->
<!--<embed height="100" width="400" src="rap.mp3"></embed> !-->
</body>
</html>