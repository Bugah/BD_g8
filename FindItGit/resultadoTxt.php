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

$termos = explode(" ", $_SESSION["texto"]);
// print_r($termos);
$mainRes = "SELECT Nome FROM TABIMG WHERE ";
foreach ($termos as $t) {
	$mainRes .= "tags LIKE ('% {$t} %') AND ";
}

$mainRes = substr($mainRes, 0, -5) ;
// print_r($mainRes);

$mainRes2 = "SELECT Nome FROM TABIMG WHERE ";
foreach ($termos as $t) {
	$mainRes2 .= "tags LIKE ('% {$t} %') OR ";
}

$mainRes2 = substr($mainRes2, 0, -4) ;
// echo "<br><br><br><br><br>";
// print_r($mainRes2);
// echo "<br><br><br><br><br>";

$query_consultar = "SELECT tag FROM TAGS_RELACIONADAS WHERE relacionadas LIKE ( '% " . reset(explode(" ", $_SESSION["texto"])) . " %' );";
 //echo $query_consultar;
$resultado_consulta = mysql_query($query_consultar);

// $str1 = "SELECT Nome FROM TABIMG WHERE ";
// $str2 = "";

// Setando um valor inicial para o número de resultados
$conta = 0;
$uau = array();
if(mysql_num_rows($resultado_consulta)!=0) {
	$str1 = "UNION SELECT Nome FROM TABIMG WHERE ";
	$str2 = "";
}
else {
	$str2 = "";
	$str1 = "";
}
while ($linha = mysql_fetch_array($resultado_consulta)) {
	$str2 .= "tags LIKE ('% {$linha['tag']} %') OR ";
	//$uau[] = $linha;
}
/*
echo "ahsdhahdah----------";
print_r($uau);
 */
$str2 = substr_replace($str2 ,"",-4); // remove last OR
/*
// $fusao = array_merge($termos,$uau);
echo "ahsdhahdah----------<br><br>";
print_r($fusao);
echo "<br><br>";
 */
 
 
$full = $mainRes . " UNION " . $mainRes2 .  $str1.$str2;
 //echo $full;
 // if($str2=="")  {
 	// // Não há resultados? Nada a somar
	 // $conta += 0;
// }
// else {
	//echo "SELECT Nome FROM TABIMG where Tags like '% ". $_SESSION["texto"] ." %' LIMIT 10 OFFSET ".$offset.";"; //debug
	
	// Query das 10 próximas imagens
	//$result = mysql_query("SELECT Nome FROM TABIMG where Tags like '% " . $_SESSION["texto"] . " %' LIMIT 10 OFFSET " . $offset . ";");
	$result = mysql_query($full . " LIMIT 10 OFFSET " . $offset . ";");
	//echo $full . " LIMIT 10 OFFSET " . $offset . ";";
	// while($linha = mysql_fetch_array($result))
	// print_r($linha);
	
	// Query do número de resultados
	if($str2!="") {
		$conta = mysql_query("SELECT count(Id) FROM TABIMG where ". $str2 . ";");
		//echo "SELECT count(Id) FROM TABIMG where ". $str2 . ";";
	}
	$result2 = mysql_query($full . " ;");
	//echo $full . " ;";
	$conta2 = mysql_num_rows($result2);
	$conta = $conta2;
	// echo $conta;
	//echo "SELECT count(Id) FROM TABIMG where ". $str2 . ";";
// }

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
			<?php navPage($_SESSION["total"][0]); ?>
		</p>
	
		<?php if($_SESSION["total"][0]>0) {
		?>
		<div class="container center">
		<div class="linha">
		<?php } ?>
		<?php

$iNum = 0;
if($conta)
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
		<a target="_blank" href= "<?php echo "builtIn/mostraImagem.php?imgName=" . $img['Nome'] . ".jpg"; ?>" > <img alt="Imagem sem thumbnail" src="<?php echo "builtIn/upload/fmt/cmp/" . $img['Nome'] . ".jpg"; ?>" alt="<?php echo $img['Nome']; ?>"  /> </a>
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