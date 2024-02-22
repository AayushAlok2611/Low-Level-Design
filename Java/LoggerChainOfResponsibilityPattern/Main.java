package Java.LoggerChainOfResponsibilityPattern;

public class Main {
    public static void main(String args[]){
        /* 
        Configuring the log processors according to chain of responsibility design pattern
        
        The chain of resposnibilty is 
        infoLogProcessor -> debugLogProcessor -> errorLogProcessor
        
        For each call to log of the logProcessor we check if current type of LogProcessoe can handle this or not
        If it cant handle it then pass it onwards to the next processor.

        */ 
        LogProcessor infoLogProcessor = new InfoLogProcessor();
        LogProcessor debugLogProcessor = new DebugLogProcessor();
        LogProcessor errorLogProcessor = new ErrorLogProcessor();
        infoLogProcessor.setNext(debugLogProcessor);
        debugLogProcessor.setNext(errorLogProcessor);

        LogProcessor logProcessor = infoLogProcessor;

        logProcessor.log(LogProcessor.INFO, "Info Log Processor called");
        logProcessor.log(LogProcessor.DEBUG, "Debug Log Processor called");
        logProcessor.log(LogProcessor.ERROR, "Error Log Processor called");
        logProcessor.log(4,"Unknow log processor called");
    }
}
