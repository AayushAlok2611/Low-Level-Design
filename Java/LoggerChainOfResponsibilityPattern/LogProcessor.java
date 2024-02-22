package Java.LoggerChainOfResponsibilityPattern;

public abstract class LogProcessor {
    public static final int INFO = 1;
    public static final int DEBUG = 2;
    public static final int ERROR = 3;
    private LogProcessor nextLogProcessor;

    public void setNext(LogProcessor logProcessor){
        this.nextLogProcessor = logProcessor;
    }
    public void log(int logType,String msg){
        if(this.nextLogProcessor != null) this.nextLogProcessor.log(logType,msg);
        else{
            System.out.println("Either log processors not configured properly or the logType is invalid");
        }
    }
} 
