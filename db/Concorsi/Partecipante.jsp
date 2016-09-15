<%@page import="java.io.*"%>
<%@page import="java.util.*"%>
<%@page import="did.*"%>
<%@page import="java.sql.*"%>

<html>
<%
Vector partecipante = (Vector)request.getAttribute("partecipante");
Vector prove = (Vector)request.getAttribute("prove");
Vector concorso = (Vector)request.getAttribute("concorso");
PartecipantiBean prt;
ProvaBean pb;
ConcorsoBean con;
%>
<head>
	<title>Partecipante</title>
</head>

<body>

<h1 align="center">
	<img src="/Concorsi/html/concorso.jpg" width="50" height="50" alt="Logo">
	Riepilogo dati
<br>
</h1>

<%
if (concorso.size()==0) {
	if (partecipante.size()==1) { %>
		<h3 align="center"><%= "0 Concorsi Registrati" %></h3>
			<br>
				<% prt = (PartecipantiBean)partecipante.get(0); %>
				<div align="center">
					<table>
						<tr>
							<th>
								Cognome:&nbsp;
							</th>
							<td>
								<%=prt.getCognome() %>
							</td>
						</tr>
						<tr>
							<th>
								Nome:&nbsp;
							</th>
							<td>
								<%=prt.getNome() %>
							</td>
						</tr>
						<tr>
							<th>
								CF:&nbsp;
							</th>
							<td>
								<%=prt.getCF() %>
							</td>
						</tr>
						<tr>
							<th>
								E-mail:&nbsp;
							</th>
							<td>
								<%=prt.getMail() %>
							</td>
						</tr>
						<tr>
							<th>
								Data di Nascita:&nbsp;
							</th>
							<td>
								<%=prt.getData() %>
							</td>
						</tr>
						<tr>
							<th>
								Luogo di Nascita:&nbsp;
							</th>
							<td>
								<%=prt.getLuogo() %>
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;
							</td>
						</tr>
					</table>
				</div>
	<% }
	else { %>
		<h3 align="center"><%= "Utente Non Iscritto" %></h3>		
<% 	}
} 
else {  %>

<%
for (int i=0; i<concorso.size(); i++) {
	prt = (PartecipantiBean)partecipante.get(i);
	con = (ConcorsoBean)concorso.get(i); %>
	<p align="center">
		<table border="1">
			<tr>
				<th width="20%">
					<font color="red">Concorso</font>
					<br>
				<br>
				<table>
					<tr>
						<th>
								Concorso:&nbsp;
							</th>
						<td>
								<%=con.getID() %>
							</td>
					</tr>
					<tr>
						<th>
							Nome:&nbsp;
						</td>
						<td>
								<%=con.getNome() %>
							</td>
					</tr>
				</table>
				</th>
				<td width="70%" align="center">
					<b><font color="red">Dati personali</font></b>
					<br>
					<br>
					<table>
						<tr>
							<th>
								Cognome:&nbsp;
							</th>
							<td>
								<%=prt.getCognome() %>
							</td>
						</tr>
						<tr>
							<th>
								Nome:&nbsp;
							</th>
							<td>
								<%=prt.getNome() %>
							</td>
						</tr>
						<tr>
							<th>
								CF:&nbsp;
							</th>
							<td>
								<%=prt.getCF() %>
							</td>
						</tr>
						<tr>
							<th>
								E-mail:&nbsp;
							</th>
							<td>
								<%=prt.getMail() %>
							</td>
						</tr>
						<tr>
							<th>
								Data di Nascita:&nbsp;
							</th>
							<td>
								<%=prt.getData() %>
							</td>
						</tr>
						<tr>
							<th>
								Luogo di Nascita:&nbsp;
							</th>
							<td>
								<%=prt.getLuogo() %>
							</td>
						</tr>
						<tr>
							<td>
								&nbsp;
							</td>
						</tr>
					</table>
				</td>
			</tr>
		</table>
		<br>
		<table>
			<tr>
				<td>
					<table border="0">
						<tr>
							<th>
								&nbsp;Codice&nbsp;
							</th>
							<th>
								&nbsp;Data&nbsp;
							</th>
							<th>
								&nbsp;Ora&nbsp;
							</th>
							<th>
								&nbsp;Luogo&nbsp;
							</th>
							<th>
								&nbsp;Tipo&nbsp;
							</th>
							<th>
								&nbsp;Esito&nbsp;
							</th>
						</tr>
						<% for (int j=0; j<prove.size(); j++) { 
							pb = (ProvaBean)prove.get(j); 
							if(pb.getIDC()==con.getID()){ %>
								<tr align="center">
									<td>
										<%=pb.getNome() %>
									</td>
									<td>
										&nbsp;<%=pb.getData() %>&nbsp;
									</td>
									<td>
										&nbsp;<%=pb.getOra() %>&nbsp;
									</td>
									<td>
										&nbsp;<%=pb.getLuogo() %>&nbsp;
									</td>
									<td>
										&nbsp;<%=pb.getTipo() %>&nbsp;
									</td>
									<td>
										<%=pb.getVoto() %>
									</td>
								</tr>
							<% 
							} 
						} %>
					</table>
				</td>
			</tr>
			<tr>
				<th>
					<br>
					<font color="red">Esito finale:&nbsp;</font><% if(prt.getEsito()==null) { %>
																								<%= "Non Deciso" %>
																							<% } 
																							else { %>
																								<%= prt.getEsito() %>
																							<% } %>
				</th>
			</tr>
		</table>
		___________________________________________________
	<br>
	</p>
<% } 
} %>
	<div align="center"><input type="button" onclick="parent:location='main'" value="Home"></div>
</body>
</html>
