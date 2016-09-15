<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="did.*"%>
<%@page import="java.sql.*"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN""http://www.w3.org/TR/REC-html40/loose.dtd">
<html>
<head>
	<title>Pagina del Concorso</title>
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
<%
Vector presidente = (Vector)request.getAttribute("presidente");
Vector membri = (Vector)request.getAttribute("membri");
Vector prove = (Vector)request.getAttribute("prove");
Vector concorso = (Vector)request.getAttribute("concorso");

CommissioneBean com;
ProvaBean pr;
ConcorsoBean con;

con = (ConcorsoBean)concorso.get(0);
com = (CommissioneBean)presidente.get(0);
%>
<div align="center">
	<h1>Concorso num: <%=con.getID() %></h1>
	<table border="1">
		<tr>
			<th>
				Nome
			</th>
			<th>
				Data Emissione
			</th>
			<th>
				Data Scandeza
			</th>
			<th>
				Commissione
			</th>
		</tr>
			<td align="center">
				<%=con.getNome() %>
			</td>
			<td align="center">
				<%=con.getDataE() %>
			</td>
			<td align="center">
				<%=con.getDataS() %>
			</td>
			<td>
				<table border="0">
					<tr>
						<td align="left">
							&nbsp;Presidente:&nbsp;<%=com.getNome() %>&nbsp;<%=com.getCognome() %>&nbsp;
						</td>
						<td align="right">
							&nbsp;Provenienza:&nbsp;<%=com.getProvenienza() %>&nbsp;
						</td>
					</tr>
						<% for(int i = 0; i<membri.size(); i++) {
							com = (CommissioneBean)membri.get(i); %>
					<tr>
						<td align="left">
							&nbsp;<%=com.getRuolo() %>:&nbsp;<%=com.getNome() %>&nbsp;<%=com.getCognome() %>&nbsp;
						</td>
						<td align="right">
							&nbsp;Provenienza: <%=com.getProvenienza() %>&nbsp;
						</td>
					</tr>
						<% } %>
				</table>
			</td>
		</tr>
	</table>
	<br>
	<br>
	<table border="0">
		<tr>
			<th>
				&nbsp;Prova&nbsp;
			</th>
			<th>
				Data
			</th>
			<th>
				Ora
			</th>
			<th>
				&nbsp;Luogo&nbsp;
			</td>
			<th>
				Tipo
			</th>
		</tr>
		<% for(int i = 0; i<prove.size(); i++) {
			pr = (ProvaBean)prove.get(i); %>
		<tr>
			<td align="center">
				<%=pr.getNome()%>
			</td>
			<td>
				&nbsp;<%=pr.getData()%>&nbsp;
			</td>
			<td>
				&nbsp;<%=pr.getOra()%>&nbsp;
			</td>
			<td>
				&nbsp;<%=pr.getLuogo()%>&nbsp;
			</td>
			<td align="center">
				&nbsp;<%=pr.getTipo()%>&nbsp;
			</td>
		</tr>
		<% } %>
	</table>
	<br>
		<input type="button" onclick="parent:location='main?ps=domanda&id=<%=con.getID()%>'" value="Iscriviti">
		<input type="button" onclick="parent:location='main'" value="Home">
	<br>
	<br>
	<br>
	<br>
	<i>Accedi alla tua area personale</i><br>
	<form name="form1" action="main" method="get" onsubmit="return validate();">
		<INPUT TYPE="HIDDEN" NAME="ps" VALUE="riepilogo">
		Username: <input type="text" name="login_pa" /><br>
		Password: <input type="password" name="password_pa" /><br>
		<input type="submit" value="Accedi" />
	</form>
</div>
</body>
</html>

