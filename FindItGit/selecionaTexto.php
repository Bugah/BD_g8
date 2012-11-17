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
				$("#pPrescisao").hide();
				
				$("#avancado").click(function() {
					$("#pPrescisao").toggle(500);
				});
			});
			
			function confereImg(w,x) {
				if(w.value) {
					document.getElementById("submeter").disabled=false;
				}
			}
			
			function vai(x) {
					document.getElementById("precisao").value=x;
					// var temp = "pre"+x;
					// var temp2 = "pre"+(1+(x+1)%3);
					// var temp3 = "pre"+(1+(x+2)%3);
					// document.getElementById(temp).style.background = "yellow";
					// document.getElementById(temp2).style.background = "white"; 
					// document.getElementById(temp3).style.background = "white"; 
			}
			
			function nvai(x) {
					alert(document.getElementById("precisao").value);
			}
			
			function valida() {
				if(document.getElementById("texto").value) {
					document.getElementById("submeter").disabled=false;
					document.getElementById("upForm").submit();
				}
				return false;
			}
			
		</script>
</head>


<body>
<?php
require_once 'menu.php';
// Mantém o tipo da busca
if (isset($_REQUEST['buscaTipo'])) {
	$_SESSION["tipo"] = $_REQUEST['buscaTipo'];
}
?>

<h1>Busca via texto</h1>

<!-- Formulário para receber aquisições !-->
<form id="upForm" action="resultadoTxt.php" method="post" enctype="multipart/form-data" onsubmit="return valida()">
	<p>
		<label for="texto">Insira as palavras-chave da imagem: </label> 
		<input type="text" class="text" name="texto" id="texto" value="" size="50" maxlength="100" autofocus="" onchange="confereImg(this)"/>
		
		<input id="submeter" type="submit" value="Buscar" onclick="return valida();" />
<!-- 		<input type="button" id="avancado" value="Avançado"/> -->
	</p>
	<p id="pPrescisao">
		Precisão de busca: 
<!-- 		<input type="hidden" name="precisao" id="precisao" value=2 /> -->
		
		<input type="button" style="background: #ffabba;" id="pre1" value=1 onclick="vai(1);"/>
		<input type="button" style="background: lightblue;" id="pre2" value=2 onclick="vai(2);"/>
		<input type="button" style="background: lightyellow;" id="pre3" value=3 onclick="vai(3);"/>
		<input type="button" id="pre0" value="OFF" onclick="vai(0);"/>
		&bull;	
		<?php 
			if(isset($_SESSION["precisao"]))
				$padrao = $_SESSION["precisao"];
			else
				$padrao = 0;
			?>
		<input type="text" style="background: black;color: white;text-align:center;" name="precisao" id="precisao"  size=1 value=<?php echo $padrao ?> />
<!-- 		<input type="button" value=Baoe onclick="nvai();"/> -->
	</p>
</form>
<?php

?>

<!-- Música para relaxar! :o) !-->
<!--<embed height="100" width="400" src="rap.mp3"></embed> !-->
</body>
</html>