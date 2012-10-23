<!-- Página que retorna o resultado da busca textual !-->

<!DOCTYPE HTML>
<?php

require_once 'connect.php';
acionaTempo();

// Obtendo o offset para divir a busca por páginas de resposta
if (isset($_REQUEST["nPage"])) {
	$offset = $_REQUEST["nPage"];
	// Pega o número da página
} else {
	$_SESSION["texto"] = $_REQUEST["texto"];
	// Primeira página
	$offset = 0;
}

//echo "SELECT Nome FROM TABIMG where Tags like '% ". $_SESSION["texto"] ." %' LIMIT 10 OFFSET ".$offset.";"; //debug

// Query das 10 próximas imagens
$result = mysql_query("SELECT Nome FROM TABIMG where Tags like '% " . $_SESSION["texto"] . " %' LIMIT 10 OFFSET " . $offset . ";");

// Query do número de resultados
$conta = mysql_query("SELECT count(Id) FROM TABIMG where Tags like '% " . $_SESSION["texto"] . " %';");


?>
<html>

	<head>
		<!-- incluindo jQuery !-->
		<script src="jquery-1.8.2.min.js"></script>
	</head>

	<body>

		<?php
		require_once 'menu.html';
		include_once 'selecionaTexto.php';
		?>
		
		<!-- Centralizando texto !-->
		<p class="centerTxt">
		<?php
		// Imprimindo informações
		echo "Buscando por <span class='resultado'>" . $_SESSION["texto"] . "</span>. <br />";
		
		$_SESSION["total"] = mysql_fetch_array($conta, MYSQL_NUM);
		echo "Foram encontrados " . $_SESSION["total"][0] . " resultados.<br .>";
		mostraTempo();
		?>
		</p>
		
		<p class="centerTxt">
			<?php navPage($_SESSION["total"][0]); ?>
		</p>
	
		<?php if($_SESSION["total"][0]>0) {
		?>
		<div class="container center">
		<div class="linha">
		<?php } ?>
		<?php

$iNum = 0;
while($img = mysql_fetch_array($result))
{

		?>

		<p>
		<?php
			// Verifica se há mais imagens a serem impressas numa nova linha
			if($iNum > 0 && $iNum%3==0) {	?>
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
		<?php echo $img[0]; ?>
		</div>

		<!-- Colocando a imagem !-->
		<a target="_blank" href= "<?php echo "builtIn/upload/fmt/" . $img['Nome'] . ".jpg"; ?>" > <img src="<?php echo "builtIn/upload/fmt/cmp/" . $img['Nome'] . ".jpg"; ?>" alt="<?php echo $img['Nome']; ?>"  /> </a>
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
if($total > 10) {
$_SESSION['res'] = $result;

$j = 0;
while($total > 0) {
		?>
		<a href="?nPage=<?php echo 10 * $j; ?>"><?php echo $j + 1; ?></a>
		<?php
		$total -= 10;
		$j++;
		}
		}
		?>
		</p>
		
		<?php
		/*
$result = mysql_query("SELECT * FROM TABIMG where Tags like '% ". $_SESSION["texto"] ." %';" );
while($row = mysql_fetch_array($result))
{
echo $row['Nome'];
echo "<br />";
		?>
		<a target="_blank" href= "<?php echo "builtIn/upload/fmt/" . $row['Nome'] . ".jpg"; ?>" > <img src="<?php echo "builtIn/upload/fmt/" . $row['Nome'] . ".jpg"; ?>" alt="<?php echo $row['Nome']; ?>"  /> </a>
		<?php
		}
		
		 */
		 
		?>

		
	</body>
</html>