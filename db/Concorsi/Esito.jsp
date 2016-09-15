<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="did.*"%>
<%@page import="java.sql.*"%>

<html>
<head>
	<title>Esito</title>
</head>
<body>
<h1 align="center">Esito:</h1>
<br>
<div align="center">
	<% String vuoto = (String)request.getAttribute("vuoto");
	if(vuoto.equals("iscritto")) { %>
	<font color="green">Registrazione avvenuta con successo!</font>
		<% if(request.getParameter("id")==null) {
			Vector esito = (Vector)request.getAttribute("esito");
			EsitoBean ris=(EsitoBean)esito.get(0); %>
			<br>
			Le tue credenziali d'accesso:
			<br>
			<br>
			<table border=1>
				<tr>
					<th>
						Login
					</th>
					<th>
						Password
					</th>
				</tr>
				<tr>
					<td>
						<%=ris.getLogin()%>
					</td>
					<td>
						<%=ris.getPassword()%>
					</td>
				</tr>
			</table>
			<%
		}
	}
	else if (vuoto.equals("vuoto")){ %>
		Concorso gia' iscritto
	<% } 
	else if (vuoto.equals("no")) {
	%>
		Errore nell'inserimento!
	<% } 
	else { %>
		<font color="green">Registrazione avvenuta con successo!</font>
	<% } %>
	<p>
		<input type="button" onclick="parent:location='main'" value="Home">
	</p>
</div>
</body>
</html>
