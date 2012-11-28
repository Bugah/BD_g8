<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
	"http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<style type="text/css">
		@import "../style.css"
	</style>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<meta http-equiv="Content-Language" content="en" />
	<meta name="GENERATOR" content="PHPEclipse 1.2.0" />
	<title>title</title>
</head>
<body>

<div class="center">
<div id="upInfo" style="background-color:#FFFFAA;padding:5px;margin-right:10px;float:left;">
<?php
$allowedExts = array("jpg", "jpeg", "gif", "png");
$extension = end(explode(".", $_FILES["file"]["name"]));
if ((($_FILES["file"]["type"] == "image/gif")
|| ($_FILES["file"]["type"] == "image/jpeg")
|| ($_FILES["file"]["type"] == "image/jpg")
|| ($_FILES["file"]["type"] == "image/png")
|| ($_FILES["file"]["type"] == "image/pjpeg"))
&& ($_FILES["file"]["size"] < 200000)
&& in_array($extension, $allowedExts))
  {
  if($_POST["titulo"]) {
  	// Validando a entrada. Evitando Injections com '.', ',', '/', '\', '|'
  	$carac = array(".",",","/","\\","|");						// caracteres ilegais
  	$_POST["titulo"] = str_replace($carac,"",$_POST["titulo"]); // retirando caracteres
  	$tok = strtok($_FILES["file"]["type"],"/"); 				// procurando a extensão original do arquivo
  	$_FILES["file"]["name"] = $_POST["titulo"].".".strtok("");
  	?><h3><?php
  	echo "Novo título: <i>".$_POST["titulo"]."</i>.";
  	?></h3><?php
  }

	// Se ocorrer erro no upload  	
  if ($_FILES["file"]["error"] > 0)
    {
    echo "Error: " . $_FILES["file"]["error"] . "<br />";
    }
	// Erro de tipo de entrada
  else
    {
    ?><i><?php
    echo "Upload: " . $_FILES["file"]["name"] . "<br />";
    echo "Tipo: " . $_FILES["file"]["type"] . "<br />";
    echo "Tamanho: " . ($_FILES["file"]["size"] / 1024) . " Kb<br />";
    echo "Localizado em: " . $_FILES["file"]["tmp_name"]. " <br /><br />";
    ?></i><?php
    }
    if (file_exists("upload/" . $_FILES["file"]["name"]))
      {
      echo $_FILES["file"]["name"] . " já existe. ";
      }
    else
      {
      move_uploaded_file($_FILES["file"]["tmp_name"],
      "upload/" . $_FILES["file"]["name"]);
      
	  /******************************************************************************/
	  // Criando o descritor de imagens no formato .info através do script criaInfo.sh
      error_reporting(E_ALL);

		/* Add redirection so we can get stderr. */
		echo '/bin/sh criaInfo.sh "'.$_REQUEST['desc']. '" "upload/' .substr($_FILES["file"]["name"], 0, -4). '" 2>&1';
		//echo "<br />";
		$handle = popen('/bin/sh criaInfo.sh "'.$_REQUEST['desc']. '" "upload/' .substr($_FILES["file"]["name"], 0, -4). '" 2>&1', 'r');
		//$handle = popen('/bin/pwd', 'r');
		//echo "'$handle'; " . gettype($handle) . "\n";
		//$read = fread($handle, 2096);
		//echo $read;
		pclose($handle);
	  /******************************************************************************/

        /* Buscar tags relacionadas */
        $tags = str_replace(' ', '-', $_REQUEST['tags'];
        $tags = explode(',',$tags);

        // QUERY:
        $cn = mysql_connect($host, $user, $pass) or die ("<br><br><center>Problemas ao conectar no servIDor: " . mysql_error() . "</center>");
        $banc = mysql_select_db($base) or die ("<br><br><center>Problemas ao selecionar a base de dados do sistemas: " . mysql_error() . "</center>");

        foreach ($tags as $tag) {
          $query_consultar = "SELECT EXISTS (SELECT 1 FROM TAGS_RELACIONADAS_FINAL WHERE tags = \"{$tag}\")"
          $resultado_consulta = mysql_query($query_consultar);
          if (!$resultado_consulta) shell_exec("ruby related.rb {$tag} > /dev/null 2>&1 &");
        }
	  
      echo "Local do arquivo: " . "upload/" . $_FILES["file"]["name"];
      }
	  ?>
	 	<h2>Visualização da Imagem:</h2>
		<img style="max-width:70%;" src="<?php echo "upload/".$_FILES["file"]["name"]; ?>" />
		
		<h2>Descrição da Imagem:</h2>
		<?php
		if(file_exists("upload/".substr($_FILES["file"]["name"], 0, -4).".info")) {
			$lines = file("upload/".substr($_FILES["file"]["name"], 0, -4).".info");
		
		// Loop through our array, show HTML source as HTML source; and line numbers too.
			foreach ($lines as $line_num => $line) {
			    echo htmlspecialchars($line);
			}
		} else {
			echo "<h3 style='color:red;'>Imagem sem descrição</h3>";
		}
		?>
		</div>
<?php
  }
	else
  {
  	echo "<h2>Erro</h2>";
	echo $_FILES["file"]["name"];
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
?>
<p><input type="button" value="Sair" onclick="window.location='../inserir.php'" /></p>
</div>



</div>

</body>
</html>
