#pragma once
#include <stdarg.h>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[13] <= 0.5) {
                            if (x[8] <= 0.5) {
                                if (x[6] <= 0.5) {
                                    if (x[14] <= 0.5) {
                                        if (x[12] <= 0.5) {
                                            if (x[19] <= 0.5) {
                                                if (x[18] <= 0.5) {
                                                    return 1;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }

                                            else {
                                                return 1;
                                            }
                                        }

                                        else {
                                            return 3;
                                        }
                                    }

                                    else {
                                        if (x[20] <= 0.5) {
                                            return 1;
                                        }

                                        else {
                                            return 2;
                                        }
                                    }
                                }

                                else {
                                    return 2;
                                }
                            }

                            else {
                                if (x[0] <= 0.5) {
                                    if (x[2] <= 0.5) {
                                        if (x[12] <= 0.5) {
                                            if (x[15] <= 0.5) {
                                                return 1;
                                            }

                                            else {
                                                if (x[16] <= 0.5) {
                                                    return 2;
                                                }

                                                else {
                                                    return 1;
                                                }
                                            }
                                        }

                                        else {
                                            return 3;
                                        }
                                    }

                                    else {
                                        if (x[5] <= 0.5) {
                                            return 3;
                                        }

                                        else {
                                            return 2;
                                        }
                                    }
                                }

                                else {
                                    if (x[20] <= 0.5) {
                                        if (x[11] <= 0.5) {
                                            if (x[9] <= 0.5) {
                                                if (x[3] <= 0.5) {
                                                    return 3;
                                                }

                                                else {
                                                    return 1;
                                                }
                                            }

                                            else {
                                                return 2;
                                            }
                                        }

                                        else {
                                            if (x[10] <= 0.5) {
                                                return 3;
                                            }

                                            else {
                                                if (x[14] <= 0.5) {
                                                    if (x[23] <= 0.5) {
                                                        return 1;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }

                                                else {
                                                    if (x[23] <= 0.5) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    else {
                                        if (x[15] <= 0.5) {
                                            if (x[11] <= 0.5) {
                                                return 2;
                                            }

                                            else {
                                                if (x[17] <= 0.5) {
                                                    if (x[12] <= 0.5) {
                                                        return 1;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }

                                                else {
                                                    if (x[22] <= 0.5) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 2;
                                                    }
                                                }
                                            }
                                        }

                                        else {
                                            if (x[17] <= 0.5) {
                                                return 3;
                                            }

                                            else {
                                                if (x[14] <= 0.5) {
                                                    if (x[12] <= 0.5) {
                                                        return 1;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        else {
                            if (x[22] <= 0.5) {
                                if (x[17] <= 0.5) {
                                    if (x[15] <= 0.5) {
                                        if (x[14] <= 0.5) {
                                            return 2;
                                        }

                                        else {
                                            return 1;
                                        }
                                    }

                                    else {
                                        return 2;
                                    }
                                }

                                else {
                                    if (x[6] <= 0.5) {
                                        if (x[8] <= 0.5) {
                                            if (x[21] <= 0.5) {
                                                if (x[18] <= 0.5) {
                                                    return 1;
                                                }

                                                else {
                                                    if (x[20] <= 0.5) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 1;
                                                    }
                                                }
                                            }

                                            else {
                                                if (x[0] <= 0.5) {
                                                    return 3;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[4] <= 0.5) {
                                                return 2;
                                            }

                                            else {
                                                return 3;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[20] <= 0.5) {
                                            if (x[5] <= 0.5) {
                                                if (x[3] <= 0.5) {
                                                    return 1;
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }

                                            else {
                                                if (x[16] <= 0.5) {
                                                    if (x[21] <= 0.5) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[9] <= 0.5) {
                                                if (x[0] <= 0.5) {
                                                    return 1;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }

                                            else {
                                                if (x[5] <= 0.5) {
                                                    return 3;
                                                }

                                                else {
                                                    if (x[4] <= 0.5) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            else {
                                if (x[4] <= 0.5) {
                                    if (x[2] <= 0.5) {
                                        if (x[0] <= 0.5) {
                                            if (x[8] <= 0.5) {
                                                return 3;
                                            }

                                            else {
                                                if (x[5] <= 0.5) {
                                                    if (x[6] <= 0.5) {
                                                        return 2;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }

                                        else {
                                            return 2;
                                        }
                                    }

                                    else {
                                        if (x[17] <= 0.5) {
                                            if (x[7] <= 0.5) {
                                                return 1;
                                            }

                                            else {
                                                if (x[18] <= 0.5) {
                                                    return 1;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[9] <= 0.5) {
                                                if (x[14] <= 0.5) {
                                                    return 3;
                                                }

                                                else {
                                                    return 1;
                                                }
                                            }

                                            else {
                                                if (x[11] <= 0.5) {
                                                    return 3;
                                                }

                                                else {
                                                    if (x[6] <= 0.5) {
                                                        return 3;
                                                    }

                                                    else {
                                                        return 3;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }

                                else {
                                    if (x[1] <= 0.5) {
                                        if (x[2] <= 0.5) {
                                            if (x[15] <= 0.5) {
                                                return 1;
                                            }

                                            else {
                                                if (x[3] <= 0.5) {
                                                    return 2;
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }
                                        }

                                        else {
                                            if (x[7] <= 0.5) {
                                                return 1;
                                            }

                                            else {
                                                return 2;
                                            }
                                        }
                                    }

                                    else {
                                        if (x[7] <= 0.5) {
                                            if (x[11] <= 0.5) {
                                                if (x[8] <= 0.5) {
                                                    return 1;
                                                }

                                                else {
                                                    return 3;
                                                }
                                            }

                                            else {
                                                return 2;
                                            }
                                        }

                                        else {
                                            if (x[16] <= 0.5) {
                                                if (x[19] <= 0.5) {
                                                    return 3;
                                                }

                                                else {
                                                    return 2;
                                                }
                                            }

                                            else {
                                                if (x[0] <= 0.5) {
                                                    return 2;
                                                }

                                                else {
                                                    return 0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    /**
                    * Predict readable class name
                    */
                    const char* predictLabel(float *x) {
                        return idxToLabel(predict(x));
                    }

                    /**
                    * Convert class idx to readable name
                    */
                    const char* idxToLabel(uint8_t classIdx) {
                        switch (classIdx) {
                            case 0:
                            return "Idle";
                            case 1:
                            return "Push In";
                            case 2:
                            return "Swipe Left";
                            case 3:
                            return "Swipe Right";
                            default:
                            return "Houston we have a problem";
                        }
                    }

                protected:
                };
            }
        }
    }