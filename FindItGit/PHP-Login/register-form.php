<?php
	session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>FindIt - Cadastro de usuário</title>
<!-- <link href="loginmodule.css" rel="stylesheet" type="text/css" /> -->
<link href="../style.css" rel="stylesheet" type="text/css" />
</head>
<body class="fundaoEstiloso">
	<?php require_once 'menu.php'; ?>
<?php
	if( isset($_SESSION['ERRMSG_ARR']) && is_array($_SESSION['ERRMSG_ARR']) && count($_SESSION['ERRMSG_ARR']) > 0 ) {
		echo '<ul class="err">';
		foreach($_SESSION['ERRMSG_ARR'] as $msg) {
			echo '<li>',$msg,'</li>'; 
		}
		echo '</ul>';
		unset($_SESSION['ERRMSG_ARR']);
	}
?>
<form id="loginForm" name="loginForm" method="post" action="register-exec.php">
  <table width="400" border="0" align="center" cellpadding="2" cellspacing="0">
    <tr>
      <th>Nome </th>
      <td><input name="nome" type="text" class="textfield" id="nome" /></td>
    </tr>
    <tr>
      <th>Sobrenome </th>
      <td><input name="sobrenome" type="text" class="textfield" id="sobrenome" /></td>
    </tr>
    <tr>
      <th width="124">Login</th>
      <td width="168"><input name="login" type="text" class="textfield" id="login" /></td>
    </tr>
    <tr>
      <th>Senha</th>
      <td><input name="senha" type="password" class="textfield" id="senha" /></td>
    </tr>
    <tr>
      <th>Confirme senha </th>
      <td><input name="csenha" type="password" class="textfield" id="csenha" /></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td><input type="submit" name="Submit" value="Registrar" /></td>
    </tr>
  </table>
</form>
</body>
</html>
