#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include <iostream>
#include <string>
#include <optional>
#include "../Calculator/Calculator.h"
#include "../Calculator/RemoteControl.h"
#include "../Calculator/Countable.h"
#include "../Calculator/FunctionExpression.h"
#include "../Calculator/FunctionIdentifier.h"
#include "../Calculator/Variable.h"

SCENARIO("calculator test") {

    GIVEN("calculator") {

        Calculator calculator;

        THEN("declare variables") {
            REQUIRE(calculator.DeclareVariable("Abc") == true);
            REQUIRE(calculator.DeclareVariable("1Abc") == false);
            REQUIRE(calculator.DeclareVariable("A123") == true);
            REQUIRE(calculator.DeclareVariable("A123_") == true);
            REQUIRE(calculator.DeclareVariable("A123") == false);
            REQUIRE(calculator.DeclareVariable("A__12") == true);
            
            AND_THEN("declare functions") {
                REQUIRE(calculator.DeclareFunction("A__12", "a-b") == false);
                REQUIRE(calculator.DeclareFunction("func", "Abc+A12") == false);
                REQUIRE(calculator.DeclareFunction("func", "Abc+A123") == true);
                REQUIRE(calculator.DeclareFunction("func2", "A123") == true);
                REQUIRE(calculator.DeclareFunction("func2", "A123_+A123") == false);

                AND_THEN("setting values") {
                    REQUIRE(calculator.SetVariableValue("A123", "5") == true);
                    REQUIRE(calculator.SetVariableValue("A123", "258") == true);
                    REQUIRE(calculator.SetVariableValue("A123", "A__12") == true);
                }
            }
        }


        /*WHEN("turning engine on") {
            car.TurnOnEngine();

            THEN("engine is turned on") {
                REQUIRE(car.IsTurnedOn() == true);
                Car::Direction dir = car.GetDirection();
                std::string dirStr = CarHandler::GetDirection(dir);
                REQUIRE(dirStr == "static");
                REQUIRE(car.GetSpeed() == 0);
                REQUIRE(car.GetGear() == 0);
            }
            AND_WHEN("setting gear to 1") {
                car.SetGear(1);
                THEN("engine is turned on and the gear is 1") {
                    REQUIRE(car.IsTurnedOn() == true);
                    Car::Direction dir = car.GetDirection();
                    std::string dirStr = CarHandler::GetDirection(dir);
                    REQUIRE(dirStr == "static");
                    REQUIRE(car.GetSpeed() == 0);
                    REQUIRE(car.GetGear() == 1);
                }

                AND_WHEN("engine is turned on, the gear is 1 and speed is 30") {
                    car.SetSpeed(30);
                    THEN("the size and capacity change") {
                        REQUIRE(car.IsTurnedOn() == true);
                        Car::Direction dir = car.GetDirection();
                        std::string dirStr = CarHandler::GetDirection(dir);
                        REQUIRE(dirStr == "forward");
                        REQUIRE(car.GetSpeed() == 30);
                        REQUIRE(car.GetGear() == 1);
                    }
                }
            }
        }

        WHEN("turning engine on, setting gear to 1 and setting speed to 10") {
            car.TurnOnEngine();
            car.SetGear(1);
            car.SetSpeed(10);
            THEN("changing speed") {
                REQUIRE(car.SetSpeed(0) == true);
                REQUIRE(car.SetSpeed(30) == true);
                REQUIRE(car.SetSpeed(31) == false);
                REQUIRE(car.SetSpeed(40) == false);
                REQUIRE(car.SetSpeed(90) == false);
                REQUIRE(car.SetSpeed(151) == false);
            }
            AND_WHEN("setting speed") {
                car.SetSpeed(30);
                car.SetGear(2);
                THEN("changing speed") {
                    REQUIRE(car.SetSpeed(0) == false);
                    REQUIRE(car.SetSpeed(20) == true);
                    REQUIRE(car.SetSpeed(50) == true);
                    REQUIRE(car.SetSpeed(51) == false);
                    REQUIRE(car.SetSpeed(70) == false);
                    REQUIRE(car.SetSpeed(90) == false);
                    REQUIRE(car.SetSpeed(151) == false);
                }
                AND_WHEN("setting speed") {
                    car.SetSpeed(50);
                    car.SetGear(3);
                    THEN("changing speed") {
                        REQUIRE(car.SetSpeed(0) == false);
                        REQUIRE(car.SetSpeed(30) == true);
                        REQUIRE(car.SetSpeed(60) == true);
                        REQUIRE(car.SetSpeed(61) == false);
                        REQUIRE(car.SetSpeed(70) == false);
                        REQUIRE(car.SetSpeed(90) == false);
                        REQUIRE(car.SetSpeed(151) == false);
                    }
                    AND_WHEN("setting speed") {
                        car.SetGear(4);
                        car.SetSpeed(40);
                        THEN("changing speed") {
                            REQUIRE(car.SetSpeed(0) == false);
                            REQUIRE(car.SetSpeed(30) == false);
                            REQUIRE(car.SetSpeed(40) == true);
                            REQUIRE(car.SetSpeed(60) == true);
                            REQUIRE(car.SetSpeed(70) == true);
                            REQUIRE(car.SetSpeed(90) == true);
                            REQUIRE(car.SetSpeed(91) == false);
                            REQUIRE(car.SetSpeed(151) == false);
                        }
                        AND_WHEN("setting speed") {
                            car.SetSpeed(50);
                            car.SetGear(5);
                            THEN("changing speed") {
                                REQUIRE(car.SetSpeed(0) == false);
                                REQUIRE(car.SetSpeed(30) == false);
                                REQUIRE(car.SetSpeed(40) == false);
                                REQUIRE(car.SetSpeed(50) == true);
                                REQUIRE(car.SetSpeed(60) == true);
                                REQUIRE(car.SetSpeed(70) == true);
                                REQUIRE(car.SetSpeed(90) == true);
                                REQUIRE(car.SetSpeed(150) == true);
                                REQUIRE(car.SetSpeed(151) == false);
                            }
                        }
                    }
                }
            }
        }

        WHEN("turning engine on, setting gear to 1 and setting speed to 20") {
            car.TurnOnEngine();
            car.SetGear(1);
            car.SetSpeed(10);
            THEN("changing gear") {
                REQUIRE(car.SetGear(2) == false);
                REQUIRE(car.SetGear(3) == false);
                REQUIRE(car.SetGear(4) == false);
                REQUIRE(car.SetGear(5) == false);
                REQUIRE(car.SetGear(6) == false);
                REQUIRE(car.SetGear(0) == true);
                REQUIRE(car.SetGear(-1) == false);
                REQUIRE(car.SetGear(-2) == false);
            }
            AND_WHEN("setting speed") {
                car.SetSpeed(25);
                THEN("changing gear") {
                    REQUIRE(car.SetGear(2) == true);
                    REQUIRE(car.SetGear(1) == true);
                    REQUIRE(car.SetGear(3) == false);
                    REQUIRE(car.SetGear(4) == false);
                    REQUIRE(car.SetGear(5) == false);
                    REQUIRE(car.SetGear(6) == false);
                    REQUIRE(car.SetGear(0) == true);
                    REQUIRE(car.SetGear(-1) == false);
                    REQUIRE(car.SetGear(-2) == false);
                }

                AND_WHEN("engine is turned on, the gear is 1 and speed is 30") {
                    car.SetSpeed(30);
                    THEN("the size and capacity change") {
                        REQUIRE(car.IsTurnedOn() == true);
                        //REQUIRE(car.GetDirection() == "forward");
                        REQUIRE(car.GetSpeed() == 30);
                        REQUIRE(car.GetGear() == 1);
                    }
                }
            }
        }*/
    }
}

SCENARIO("RemoteControl test") {

    GIVEN("remote control") {
        Calculator calc;
        std::string inputStr = "var x\nprint x\nlet x=1.234\nlet x=1.234\nprint x\nlet y=x\nlet x=99\nprintvars\n";
        std::istringstream input(inputStr);
        std::ostringstream output;
        RemoteControl remoteControl(calc, input, output);
        remoteControl.HandleCommand();
        THEN("") {
            /*std::optional<double> val = calc.CountValue("x");
            if (val) {
                bool isEquial = val.value() != std::numeric_limits<double>::quiet_NaN();
                CHECK(isEquial == true);
            }*/
            
        }
        AND_WHEN("") {

        }
    }
}