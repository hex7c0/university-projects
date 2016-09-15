<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="did.*"%>
<%@page import="java.sql.*"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN""http://www.w3.org/TR/REC-html40/loose.dtd">
<html>
<%
Vector bandi = (Vector)request.getAttribute("bandi");
ConcorsoBean con;
%>	
<head>
	<title>Ufficio concorsi</title>
<script type="text/javascript">
function validate() {
var res = true;
	if (!document.form1.login_pa.value) {
		alert("Inserire dati dentro 'Login'")
		res = false;
	}
	if (!document.form1.password_pa.value) {
		alert("Inserire dati dentro 'Password'")
		res = false;
	}
	return res;
}
</script>
</head>

<body>
<div align="center">
	<h1>
		<img src="/Concorsi/html/concorsi.jpg" width="50" height="50" alt="Logo">
		Ufficio concorsi
	</h1>
	<h9>
		<i>L'Ufficio si occupa delle procedure amministrative e degli adempimenti necessari all'organizzazione delle tornate di valutazione per il reclutamento di personale.</i>
	</h9>
	<p>
	<br>
		<h2>
		<font color="red">Elenco bandi di concorso aperti</font>
		</h2>
		<table border="1">
			<tr>
				<th>
					&nbsp;Codice&nbsp;
				</th>
				<th>
					&nbsp;Nome&nbsp;
				</th>
				<th>
					&nbsp;Data Emissione&nbsp;
				</th>
				<th>
					&nbsp;Data Scadenza&nbsp;
				</th>
			</tr>
			<% for (int i=0; i<bandi.size(); i++) {
				con = (ConcorsoBean)bandi.get(i); %>
			<tr>
				<td align="center">
					<a href="main?ps=concorso&id=<%=con.getID()%>"><%=con.getID() %></a>
				</td>
				<td align="center">
					<%=con.getNome() %>
				</td>
				<td align="center">
					<%=con.getDataE() %>
				</td>
				<td align="center">
					<%=con.getDataS() %>
				</td>
			</tr>
			<% } %>
		</table>
		<br>
		<input type="button" onclick="parent:location='main?ps=iscrizione'" value="Registrazione Studente">
		<br>
		<br>
		<br>
		<br>
		<i>Accedi alla tua area personale</i><br>
		<form name="form1" action="main" method="get" onsubmit="return validate();">
			<input type="hidden" name="ps" value="riepilogo">
			Username: <input type="text" name="login_pa" /><br>
			Password: <input type="password" name="password_pa" /><br>
			<input type="submit" value="Accedi" />
		</form>
	</p>
</body>
</html>
