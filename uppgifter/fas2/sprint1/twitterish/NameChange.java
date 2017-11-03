public class NameChange implements java.io.Serializable {
    private Account newAccount;
    
    public NameChange(Account newAccount) {
        this.newAccount = newAccount;
    }

    public Account getNewAccount() {
        return this.newAccount;
    }
}









