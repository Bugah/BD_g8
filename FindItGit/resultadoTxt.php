<!-- Página que retorna o resultado da busca textual !-->

<!DOCTYPE HTML>
<?php

require_once 'connect.php';
acionaTempo();
$perPage = 20; // Quantas imagens por página

if(isset($_REQUEST["precisao"]))
	$_SESSION["precisao"] = $_REQUEST["precisao"];
else
	$_SESSION["precisao"] = 0;

// Obtendo o offset para divir a busca por páginas de resposta
if (isset($_REQUEST["nPage"])) {
	$offset = $_REQUEST["nPage"];
	// Pega o número da página
} else {
	$_SESSION["texto"] = $_REQUEST["texto"];
	// Primeira página
	$offset = 0;
}

$termos = explode(" ", $_SESSION["texto"]);

//*********************************************************************************************************
	error_reporting(E_ALL);
	/* Add redirection so we can get stderr. */
	$cmd = '/bin/sh builtIn/consulta.sh \'' . $_SESSION['texto'] . '\' 2>&1';
	// echo $cmd;
	
	/* Executa o comando e retorna a saída para $test */
	exec($cmd,$test);
	
	// echo $test;
	// print_r($test);

	foreach ($test as $tst) {
		$tmp = (int)$tst;
		$tmp = "IMG".str_pad($tmp, 6, "0", STR_PAD_LEFT);
		// echo "<br>";
		// echo $tmp;
	}
	
	$conta = sizeof($test);
	$conta2 = $conta;

// array_splice($test, $offset);
$answer = array_chunk($test, $perPage);
?>
<html>

	<head>
		<!-- incluindo jQuery !-->
		<script src="jquery-1.8.2.min.js"></script>
	</head>

	<body>

		<?php
		require_once 'menu.php';
		include_once 'selecionaTexto.php';
		?>
		
		<!-- Centralizando texto !-->
		<p class="centerTxt">
		<?php
		// Imprimindo informações
		echo "Buscando por <span class='resultado'>" . $_SESSION["texto"] . "</span>. <br />";
		$_SESSION["total"] = array();
		if($conta) {
//			$_SESSION["total"] = mysql_fetch_array($conta, MYSQL_NUM);
			
			$_SESSION["total"][0] = $conta2;
		} else {
			$_SESSION["total"][0] = 0;
		}
		echo "Foram encontrados " . $_SESSION["total"][0] . " resultados.<br />";
		mostraTempo();
		?>
		</p>
		
		<p class="centerTxt">
			<?php navPage($_SESSION["total"][0], $perPage); ?>
		</p>
	
		<?php if($_SESSION["total"][0]>0) {
		?>
		<div class="container center">
		<div class="linha">
		<?php } ?>
		<?php

$iNum = 0;
if($conta)
	// while($img = mysql_fetch_array($result))
	foreach ($answer[$offset/10] as $tst) {
		$tmp = (int)$tst;
		$img = "IMG".str_pad($tmp, 6, "0", STR_PAD_LEFT); // Formato IMGxxxxxx

		?>

		<p>
		<?php
			// Verifica se há mais imagens a serem impressas numa nova linha
			if($iNum > 0 && $iNum%5==0) {	?>
		<!-- Separa linhas  !-->
		<div class="corte">&bull;&bull;&bull;&bull;&bull;&bull;&bull;</div>
		</div>
		
		<!-- Cria outra linha !-->
		<div class="linha">
			<?php }
			$iNum++;
 ?>
			<!-- Div da Imagem !-->
			<div class="img">
			<!-- Div da Descrição !-->
			<div class="desc">
		<?php echo $img; ?>
		</div>

		<!-- Colocando a imagem !-->
		<a target="_blank" href= "<?php echo "builtIn/mostraImagem.php?imgName=" . $img . ".jpg&pesquisa='" . $_SESSION['texto'] . "'"; ?>" > <img alt="Imagem sem thumbnail" src="<?php echo "builtIn/upload/fmt/cmp250/" . $img . ".jpg"; ?>" alt="<?php echo $img; ?>"  /> </a>
		</div>

		<?php
		}
		?>
		</p>
		<br />

		<?php if($_SESSION["total"][0]>0) {
		?>
		<div class="corte">&bull;&bull;&bull;&bull;&bull;&bull;&bull;</div>
		</div>
		</div>
		<?php } ?>

<p class="centerTxt">
		<?php
		$total = $_SESSION["total"][0];
		if($total > $perPage) {
			// $_SESSION['res'] = $result;
			
			$j = 0;
			while($total > 0) {
			?>
				<a href="?nPage=<?php echo 10 * $j; ?>"><?php echo $j + 1; ?></a>
			<?php
				$total -= $perPage;
				$j++;
			}
		}
		?>
		</p>
		
		
	</body>
</html>