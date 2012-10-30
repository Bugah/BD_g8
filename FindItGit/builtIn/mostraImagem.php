<!DOCTYPE HTML>
<head>
	<title> Detalhes da Imagem <?php if(isset($_REQUEST['imgName'])) echo $_REQUEST['imgName']; ?></title>
	<script src="../jquery-1.8.2.min.js"></script>
	<style type="text/css">
		@import "../style.css"
	</style>
	<script>
		function escondeDesc() {
					$(".destaque").toggle(500);
					$(this).css("width","auto");
				}
		$(document).ready(function() {
			
				$("#zoom").click(function() {
					escondeDesc();
				});
				
			});
	</script>
</head>
<body style="background: black;">
	<div style="width:50px;display:inline;float:right;right=0;">
			<button style="float:right;right=0;" onclick="window.location='..'"><img  src="../imagens/secLogo.png" height="70px" /></button>
			<button style="float:right;color:red;font-weight:bold;display:block;" onclick="window.close();">X</button>
			<button style="float:right;color:blue;font-weight:bold;display:block;" onclick="escondeDesc();">O<br />&nbsp;&nbsp;\</button>
		</div>
	<div class="centerTxt center" style="width:100%;">
		
<?php

if(isset($_REQUEST['imgName'])) {
?>

		<p class="destaque">
			<span>Tags:</span>  
<?php
$file_handle = fopen("upload/fmt/".substr($_REQUEST['imgName'],0,-4).".tags", "r");
while (!feof($file_handle)) {
   $line = fgets($file_handle);
   echo $line;
}
fclose($file_handle);
?>
		</p>
		<p class="destaque">
			<span>Descrição:</span> 
<?php
$file_handle = fopen("upload/fmt/".substr($_REQUEST['imgName'],0,-4).".desc", "r");
while (!feof($file_handle)) {
   $line = fgets($file_handle);
   echo $line;
}
fclose($file_handle);
?>
		</p>
		<img id="zoom" class="center2" src="upload/fmt/<?php echo $_REQUEST['imgName']; ?>" />
<?php
} else {
?>

<pre>Nenhuma imagem especificada.</pre>

<?php
}
?>
</div>
</body>
</html>