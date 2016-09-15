<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="did.*"%>
<%@page import="java.sql.*"%>

<html>
<%
String id=(String)request.getAttribute("id");
%>	
<head>
	<title>Iscrizione al concorso</title>
<script type="text/javascript">
function validate() {
var res = true;
	if (!document.form1.Login.value) {
		alert("Inserire dati dentro 'Login'")
		res = false;
	}
	if (!document.form1.Password.value) {
		alert("Inserire dati dentro 'Password'")
		res = false;
	}
	return res;
}
</script>
</head>

<body>
<div align="center">
	<h1>Iscrizione al Concorso</h1>
	<br>
	<h9>
		<i>Compilare tutti i campi per completare l'iscrizione</i>
	</h9>
	<br>
	<p>
		<form name="form1" method="get" action="/Concorsi/servlet/main" onsubmit="return validate();">
			Login: <input name="Login" type="text" />
			Password: <input name="Password" type="password" />
			<input type="hidden" name="ps" value="esito">
			<input type="hidden" name="id" value=<%=id%>>
			<input type="submit">
		</form>
			<input type="button" onclick="parent:location='main'" value="Home">
	</p>
</div>
</body>
</html>
