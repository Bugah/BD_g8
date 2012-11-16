<!DOCTYPE HTML>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<style>
	@import "../style.css"
</style>
<title>FindIt - Login</title>
<link href="../style.css" rel="stylesheet" type="text/css" />
<!-- <link href="loginmodule.css" rel="stylesheet" type="text/css" /> -->
</head>
<body class="fundaoEstiloso">
<?php require_once 'menu.php'; ?>
<form id="loginForm" name="loginForm" method="post" action="login-exec.php">
  <table width="300" border="0" align="center" cellpadding="2" cellspacing="0">
    <tr>
      <th width="112"><b>Login</b></td>
      <td width="188"><input name="login" type="text" class="textfield" id="login" /></td>
    </tr>
    <tr>
      <th><b>Senha</b></td>
      <td><input name="password" type="password" class="textfield" id="password" /></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>	<input type="submit" name="Submit" value="Login" />
      		&nbsp;&nbsp;<input type="button" name="Register" value="Registrar" onclick="window.location='register-form.php';" /></td>
    </tr>
  </table>
</form>
<!-- <a href="register-form.php" style="centerTxt">Registrar</a> -->
</body>
</html>
