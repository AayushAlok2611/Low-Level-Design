package Java.LoggerChainOfResponsibilityPattern;

public class DebugLogProcessor extends LogProcessor{
    DebugLogProcessor(){}

    public void log(int logType,String msg)
    {
        if(logType == DEBUG){
            System.out.println("DEBUG: -> " + msg);
        }
        else
        {
            super.log(logType,msg);
        }
    }
}
