<!-- Sistema de upload com possibilidade de troca de título feito em PHP. !-->

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
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
</head>

<script type="text/javascript" ">
	function confere(form) {
		if(form.value == "" || form.value == " Digite a descrição da imagem aqui... ") {
			form.value = " Digite a descrição da imagem aqui... ";
		}
		form.value = " Digite a descrição da imagem aqui... ";
	}
</script>

<body>
<?php require_once 'menu.php'; ?>
<h1>Upload de imagens</h1>

<!-- Formulário para receber aquisições !-->
<form id="upForm" action="builtIn/upload.php" method="post" enctype="multipart/form-data" onsubmit="confere(this)">
	<p>
		<label for="file">Coloque o arquivo aqui:</label>
		<input type="file" id="file" name="file" size="50" maxlength="100000" accept="image/*" />
	<!-- </p><p>
		<label for="titulo">Quer um novo título?</label> 
		<input type="text" class="text" name="titulo" id="titulo" value="" size="50" maxlength="50" /> -->
	</p><p>
		<label for="tags">Palavras-chave da imagem:</label> 
		<input type="text" class="text" name="tags" id="tags" value="" size="50" maxlength="500" />
	</p><p>
		<div>
			<label for="desc" style="position:relative;bottom:30px;">Descrição da imagem:</label> 
			<textarea name="desc" rows="4" cols="50"  form="upForm" onfocus="this.value=''" onfocusout="confere(this);">	Digite a descrição da imagem aqui...</textarea>
		</div>
	</p>
	<input type="submit" value="Upload" />
</form>
<?php
?>
</body>
</html>