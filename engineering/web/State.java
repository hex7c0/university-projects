package web;


public interface State
{
    public void Logon();
    public void Logoff();
    public void Admin();
    public void Manager();
    public void keyPress(int menu);
}
