<!DOCTYPE HTML>
<html>
<head>
	<style type="text/css">
		@import "../style.css"
	</style>
	<script src="../jquery-1.8.2.min.js"></script>
	
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta http-equiv="Content-Language" content="en" />
	<meta name="GENERATOR" content="PHPEclipse 1.2.0" />
</head>
<body>
	
<!-- Removendo o carregador da página	 -->
	<script>
		// document.getElementById("loading").innerHTML = "";
		// document.getElementById("loading").style.visibility = "collapse";
		document.getElementById("loading").style.display = "none";
	</script>
	
<?php 
require_once '../connect.php';
if(isset($_FILES["file"])) {?>
	
<div class="imageView">
<?php
$allowedExts = array("jpg", "jpeg", "gif", "png");
$extension = end(explode(".", $_FILES["file"]["name"]));

/* if antigo - com problemas
 * ***************************
 * if ((($_FILES["file"]["type"] == "image/gif")
|| ($_FILES["file"]["type"] == "image/jpeg")
|| ($_FILES["file"]["type"] == "image/jpg")
|| ($_FILES["file"]["type"] == "image/png")
|| ($_FILES["file"]["type"] == "image/pjpeg"))
&& ($_FILES["file"]["size"] < 200000)
&& in_array($extension, $allowedExts))
 * */

if ($_FILES["file"]["type"] && in_array($extension, $allowedExts))
  {

	// Se ocorrer erro no upload  	
  if ($_FILES["file"]["error"] > 0)
    {
    		// Erro de tipo de entrada
    echo "Erro: " . $_FILES["file"]["error"] . "<br />";
    }
	
  if($extension!="jpg") {
  	echo "Aviso: imagem convertida para formato correto! <br />";
	   /******************************************************************************/
	  // Criando o descritor normalizado de imagens no formato .nor através do script normaliza.sh
      error_reporting(E_ALL);
		/* Add redirection so we can get stderr. */
		// echo '/bin/sh tmp/normaliza.sh '.substr($_FILES["file"]["name"], 0, -4). ' tmp/ 2>&1';
		// echo "<br />";
		$handle = popen('/bin/sh upload/toJPG.sh '. $_FILES["file"]["name"] . ' tmp/' . substr($_FILES["file"]["name"], 0, -4) . ' 2>&1', 'r');
		//$handle = popen('/bin/pwd', 'r');
		// echo "'$handle'; " . gettype($handle) . "\n";
		// $read = fread($handle, 2096);
		// echo $read;
		pclose($handle);
		$_FILES["file"]["name"] = substr($_FILES["file"]["name"], 0, -4).".jpg";
	  /******************************************************************************/
  }
    $_FILES["file"]["name"] = str_replace(" ", "_", $_FILES["file"]["name"]);
      move_uploaded_file($_FILES["file"]["tmp_name"],
      "tmp/" . $_FILES["file"]["name"]);
	  
	  
      //echo "Local do arquivo: " . "tmp/" . $_FILES["file"]["name"];
      acionaTempo();
      /******************************************************************************/
	  // Criando o descritor normalizado de imagens no formato .nor através do script normaliza.sh
      error_reporting(E_ALL);
		/* Add redirection so we can get stderr. */
		// echo '/bin/sh tmp/normaliza.sh '.substr($_FILES["file"]["name"], 0, -4). ' tmp/ 2>&1';
		// echo "<br />";
		$handle = popen('/bin/sh tmp/normaliza.sh '.substr($_FILES["file"]["name"], 0, -4). ' tmp/ 2>&1', 'r');
		//$handle = popen('/bin/pwd', 'r');
		// echo "'$handle'; " . gettype($handle) . "\n";
		// $read = fread($handle, 2096);
		// echo $read;
		pclose($handle);
	  /******************************************************************************/
	  mostraTempoAlt("normalização");
	  echo "<br />";
	  acionaTempo();
	  // Procurando imagens semelhantes
      error_reporting(E_ALL);
		/* Add redirection so we can get stderr. */
		$cmd = 'tmp/tools/BruteForceDist/BruteForceDist tmp/'.substr($_FILES["file"]["name"], 0, -4). '.nor tmp/tools/BruteForceDist/1.nor 2>&1';
		// echo "<br />";
		// echo $cmd;
		// echo "<br />";
		//$handle = popen($cmd, 'r');
		//passthru($cmd, $test);
		
		/* Executa o comando e retorna a saída para $test */
		exec($cmd,$test);
		//print_r($test);
		$imgName = array();
		$imgPoints = array();
		$i=0;
		//for($i=0;$i<20;$i++) {
			while(reset(explode(" : ", $test[$i+1]))) {
				
			// Parsing da saída do calculador
			$dois = end(explode(" : ", $test[$i+1]));
			$tmp = reset(explode(" : ", $test[$i+1]));
			$imgName[$i] = "IMG".$tmp;
			$imgPoints[$i] = $dois;
$i++;
			//echo ", ";
			//print($string[$i]);
		}
		
		$_SESSION['img'] = $imgName;
		$_SESSION['points'] = $imgPoints;
		
		//$handle = popen('/bin/pwd', 'r');
		//echo "'$handle'; " . gettype($handle) . "\n";
		//$read = fread($handle, 1024*1024);
		//echo $read;
		//pclose($handle);
	  /******************************************************************************/
      
	  ?>
	<script>
    $(window).scroll(function () { 
      $("#preview").css("opacity", "0.9");
    	$("#previewTxt").hide(2500);
      $("#preview").css("bottom", "0");  
    });

	</script>

		<div id="tst">
			<h2 id="previewTxt">Visualização da Imagem:</h2>
			<img id="preview" src="<?php echo "builtIn/tmp/".$_FILES["file"]["name"]; ?>" />
		</div>
	</div>
<?php
	include_once '../resultadoImg.php';
  }
	else
  {
  	echo "<h2>Erro</h2>";
  	if ((($_FILES["file"]["type"] != "image/gif")
	|| ($_FILES["file"]["type"] != "image/jpeg")
	|| ($_FILES["file"]["type"] != "image/png")
	|| ($_FILES["file"]["type"] != "image/pjpeg"))) 
	{
  		echo "Tipo de arquivo inválido. <br>".$_FILES["file"]["type"]." não é do tipo JPEG/PNG/GIF válido.";
	}
	else if(($_FILES["file"]["size"] > 200000)) {
		echo "Tamanho inválido. ". ($_FILES["file"]["size"] / 1024)."Kb > 2MB.";
	}
	else {
		echo "Erro desconhecido. ";
	}
  }
  }
?>

</div>

</div>

</body>
</html>
