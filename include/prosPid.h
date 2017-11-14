#include "Math.h"

class Pid {
  double kP,
    kI,
    kD,
    prop,
    integ,
    deriv,
    integLim,
    result;
  int targ,
    val,
    valLast,
    err,
    errLast,
    time,
    timeLast;
  short thresh,
    out;
  public: bool bIsEnabled,
    bIsOnTarg;

  public: Pid(double kp, double ki, double kd, short threshold, double integMax) {
   targ = 0;
    val = 0;
    err = 0;
    time = 0;
    kP = kp;
    kI = ki;
    kD = kd;
    thresh = threshold;
    integ = 0;
    bIsEnabled = true;
    integLim = integMax;
  }

  int targetSet(int target) {
    integ = 0;
    return targ = target;
  }

  int pidUpdate(int sensorVal, int time) {
    valLast = val;
    errLast = err;
    timeLast = time;
    val = sensorVal;
    err = targ - val;
    if(Math.abs(err) < thresh)
      bIsOnTarg = true;
    prop = err * kP;
    integ += err * kI;
    if(Math.abs(integ) > integLim)
      integ = integLim * Math.sgn(integ);
    deriv = (err - errLast) * kD;
    result = prop + integ + deriv;
    if(bIsOnTarg)
      out = 0;
    else
      out = Math.round(result);
    return out;
  }

  bool getMtrPwr() {
    return out;
  }

};
