<?php


$filename = "upload/fmt/".substr($_REQUEST['imgName'],0,-4);
?>
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
	<div class=barraLateral>
		<button style="float:right;color:red;font-weight:bold;display:block;" onclick="window.close();">X</button>
		<button style="float:right;right=0;" onclick="window.location='..'"><img  src="../imagens/secLogo.png" height="70px" /></button>
		
		<button style="float:right;color:blue;font-weight:bold;display:block;" onclick="escondeDesc();"><img src="../imagens/lupa.png" /> </button>
		
		<p style="float:right;color:silver;font-weight:bold;display:block;background:#252525;text-align:right;">
		<?php if(file_exists($filename.".jpg")) {
			list($width, $height, $type, $attr) = getimagesize("upload/fmt/".$_REQUEST['imgName']);
			echo "Tamanho:<br />";
			echo $width . "x" . $height;
		}?>
		</p>
		</div>
	<div class="centerTxt center" style="width:100%;">
		
<?php

if(isset($_REQUEST['imgName'])) {
?>

		<p class="destaque">
			<span>Tags:</span>  
<?php

if(file_exists($filename.".tags")) {
	// echo $_GET["pesquisa"];
	$id = (int)substr($filename, -6);
	
	$pesquisa = substr($_GET["pesquisa"], 1,-1);
	
	// echo $pesquisa;
	
	$termos = explode(' ', $pesquisa);
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Imagem, ou pelo sua tag existente, acionando treinador Davis!
	////////////////////////
	error_reporting(E_ALL);
	/* Add redirection so we can get stderr. */
	$cmd = '/bin/sh treina.sh '.$id. ' ' . $_GET["pesquisa"] . ' 2>&1';
	
	/* Executa o comando e retorna a saída para $test */
	exec($cmd,$test);
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	// $file_handle = fopen($filename.".tags", "r");
	// if($file_handle) 
	// while (!feof($file_handle)) {
	   // $line = fgets($file_handle);
	   // echo $line;
	// }
	// fclose($file_handle);
	
	$fh = fopen($filename.".tags", "rb");
	$data = fread($fh, 4096);
	foreach ($termos as $t) {
		$t = str_replace(' ', '', $t);
			// $data = str_replace(' '.$t.' ', "<span class='match'> ".$t." </span>", $data);
			$data = preg_replace('/\b'.preg_quote($t, '/').'\b/', "<span class='match'>".$t."</span>", $data);
		}
	echo $data;
}
else {
	echo "Imagem sem tags.";
}
?>
		</p>
		<p class="destaque">
			<span>Descrição:</span> 
<?php
if(file_exists($filename.".desc")) {
	$file_handle = fopen($filename.".desc", "r");
	while (!feof($file_handle)) {
	   $line = fgets($file_handle);
	   echo $line;
	}
	fclose($file_handle);
}
else {
	echo "Imagem sem descrição.";
}
?>
		</p>
		
		<img id="zoom" alt="Sem imagem" style="cursor:url(../imagens/lupa.png), auto" class="center2" src="upload/fmt/<?php echo $_REQUEST['imgName']; ?>" />
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