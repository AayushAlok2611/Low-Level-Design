package Java.LoggerChainOfResponsibilityPattern;

public class ErrorLogProcessor extends LogProcessor{
    ErrorLogProcessor(){}

    public void log(int logType,String msg)
    {
        if(logType == ERROR){
            System.out.println("ERROR: -> " + msg);
        }
        else{
            super.log(logType,msg);
        }
    }
}
