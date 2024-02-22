package Java.LoggerChainOfResponsibilityPattern;

public class InfoLogProcessor extends LogProcessor{
    InfoLogProcessor(){}

    public void log(int logType,String msg)
    {
        if(logType == INFO){
            System.out.println("INFO: -> " + msg);
        }
        else
        {
            super.log(logType,msg);
        }
    }
}
