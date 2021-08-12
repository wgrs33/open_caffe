#ifndef _OPENCAFFE_PID_CONTROLLER_H
#define _OPENCAFFE_PID_CONTROLLER_H

namespace OpenCaffe {

template <typename T>
class PidController {
public:
    PidController() {
        init();
    }
    
	PidController(T p, T i, T d) {
        init();
        P=p; I=i; D=d;
    }

	PidController(T p, T i, T d, T f) {
        init();
        P=p; I=i; D=d; F=f;
    }

	void setP(T p) {
        P=p;
        checkSigns();
    }

	void setI(T i) {
        if (I!=0) {
            errorSum=errorSum*I/i;
        }
        if (maxIOutput!=0) {
            maxError=maxIOutput/i;
        }
        I=i;
        checkSigns();
    }

	void setD(T d) {
        D=d;
        checkSigns();
    }

	void setF(T f) {
        F=f;
        checkSigns();
    }
	void setPID(T p, T i, T d) {
        P=p;I=i;D=d;
        checkSigns();
    }

	void setPID(T p, T i, T d, T f) {
        P=p;I=i;D=d;F=f;
        checkSigns();
    }

	void setMaxIOutput(T maximum){
        maxIOutput=maximum;
        if (I != 0) {
            maxError=maxIOutput/I;
        }
    }

	void setOutputLimits(T output){ 
        setOutputLimits(-output,output);
    }

	void setOutputLimits(T minimum, T maximum){
        if (maximum<minimum)
            return;
        maxOutput=maximum;
        minOutput=minimum;

        if (maxIOutput==0 || maxIOutput>(maximum-minimum)) {
            setMaxIOutput(maximum-minimum);
        }
    }

	void setDirection(bool reversed) {
        this->reversed=reversed;
    }

	void setSetpoint(T setpoint) {
        this->setpoint=setpoint;
    }

	void reset() {
        firstRun=true;
        errorSum=0;
    }

	void setOutputRampRate(T rate) {
        outputRampRate=rate;
    }

	void setSetpointRange(T range) {
        setpointRange=range;
    }

	void setOutputFilter(T strength){
        if (strength==0 || bounded(strength,0,1)) {
            outputFilter=strength;
        }
    }

	T getOutput(){
        return getOutput(lastActual,setpoint);
    }

	T getOutput(T actual) {
        return getOutput(actual,setpoint);
    }

	T getOutput(T actual, T setpoint) {
        T output;
        T Poutput;
        T Ioutput;
        T Doutput;
        T Foutput;

        this->setpoint=setpoint;

        //Ramp the setpoint used for calculations if user has opted to do so
        if (setpointRange!=0) {
            setpoint=clamp(setpoint,actual-setpointRange,actual+setpointRange);
        }

        //Do the simple parts of the calculations
        double error=setpoint-actual;

        //Calculate F output. Notice, this->depends only on the setpoint, and not the error. 
        Foutput=F*setpoint;

        //Calculate P term
        Poutput=P*error;	 

        //If this->is our first time running this-> we don't actually _have_ a previous input or output. 
        //For sensor, sanely assume it was exactly where it is now.
        //For last output, we can assume it's the current time-independent outputs. 
        if (firstRun) {
            lastActual=actual;
            lastOutput=Poutput+Foutput;
            firstRun=false;
        }


        //Calculate D Term
        //Note, this->is negative. this->actually "slows" the system if it's doing
        //the correct thing, and small values helps prevent output spikes and overshoot 

        Doutput= -D*(actual-lastActual);
        lastActual=actual;



        //The Iterm is more complex. There's several things to factor in to make it easier to deal with.
        // 1. maxIoutput restricts the amount of output contributed by the Iterm.
        // 2. prevent windup by not increasing errorSum if we're already running against our max Ioutput
        // 3. prevent windup by not increasing errorSum if output is output=maxOutput	
        Ioutput=I*errorSum;
        if (maxIOutput!=0) {
            Ioutput=clamp(Ioutput,-maxIOutput,maxIOutput); 
        }	

        //And, finally, we can just add the terms up
        output=Foutput + Poutput + Ioutput + Doutput;

        //Figure out what we're doing with the error.
        if (minOutput!=maxOutput && !bounded(output, minOutput,maxOutput)) {
            errorSum=error; 
            // reset the error sum to a sane level
            // Setting to current error ensures a smooth transition when the P term 
            // decreases enough for the I term to start acting upon the controller
            // From that point the I term will build up as would be expected
        }
        else if (outputRampRate!=0 && !bounded(output, lastOutput-outputRampRate,lastOutput+outputRampRate)) {
            errorSum=error; 
        }
        else if (maxIOutput!=0) {
            errorSum=clamp(errorSum+error,-maxError,maxError);
            // In addition to output limiting directly, we also want to prevent I term 
            // buildup, so restrict the error directly
        }
        else {
            errorSum+=error;
        }

        //Restrict output to our specified output and ramp limits
        if (outputRampRate!=0) {
            output=clamp(output, lastOutput-outputRampRate,lastOutput+outputRampRate);
        }
        if (minOutput!=maxOutput) { 
            output=clamp(output, minOutput,maxOutput);
            }
        if (outputFilter!=0) {
            output=lastOutput*outputFilter+output*(1-outputFilter);
        }

        lastOutput=output;
        return output;
    }

private:
	T clamp(T value, T min, T max) {
        if (value > max) { return max; }
        if (value < min) { return min; }
        return value;
    }

	bool bounded(T value, T min, T max) {
		return (min<value) && (value<max);
    }

	void checkSigns() {
        if(reversed){	//all values should be below zero
            if (P>0) P*=-1;
            if (I>0) I*=-1;
            if (D>0) D*=-1;
            if (F>0) F*=-1;
        }
        else{	//all values should be above zero
            if (P<0) P*=-1;
            if (I<0) I*=-1;
            if (D<0) D*=-1;
            if (F<0) F*=-1;
        }
    }
	void init() {
        P=0;
        I=0;
        D=0;
        F=0;

        maxIOutput=0;
        maxError=0;
        errorSum=0;
        maxOutput=0; 
        minOutput=0;
        setpoint=0;
        lastActual=0;
        firstRun=true;
        reversed=false;
        outputRampRate=0;
        lastOutput=0;
        outputFilter=0;
        setpointRange=0;
    }

	T P;
	T I;
	T D;
	T F;

	T maxIOutput;
	T maxError;
	T errorSum;

	T maxOutput; 
	T minOutput;

	T setpoint;

	T lastActual;

	bool firstRun;
	bool reversed;

	T outputRampRate;
	T lastOutput;

	T outputFilter;

	T setpointRange;
};

} //namespace OpenCaffe

#endif //_OPENCAFFE_PID_CONTROLLER_H