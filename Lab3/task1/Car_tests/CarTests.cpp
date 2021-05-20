#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include <iostream>
#include <string>
#include "../Car/Car.h"
#include "../Car/CarHandler.h"

SCENARIO("car") {

    GIVEN("car") {
        
        Car car;
       
        THEN("State after initialization") {
            REQUIRE(car.IsTurnedOn() == false);
            Car::Direction dir = car.GetDirection();
            std::string dirStr = CarHandler::GetDirection(dir);
            REQUIRE(dirStr == "static");
            REQUIRE(car.GetSpeed() == 0);
            REQUIRE(car.GetGear() == 0);
        }
        
        WHEN("turning engine on") {
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
                        REQUIRE(car.GetSpeed() == 30);
                        REQUIRE(car.GetGear() == 1);
                    }
                }
            }
        }
    }
}

SCENARIO("CarHandler test") {

    GIVEN("carHandler") {
        Car car;
        std::istringstream input;
        std::ostringstream output;
        CarHandler carHandler(car, input, output);

        WHEN("giving Info command") {
            input.str("Info\n");
            carHandler.HandleCommand();
            
            THEN("info is shown") {
                CHECK(output.str() == "The Engine is turned off.\nDirection is static.\nSpeed is 0.\nGear is 0.\n");
            }
            AND_WHEN("giving EngineOn command") {
                input.str("EngineOn\n");
                output.str("");
                carHandler.HandleCommand();

                THEN("the engine was turned on") {
                    CHECK(output.str() == "Car's engine has been turned on.\n");
                }

                AND_WHEN("giving command SetGear") {
                    input.str("SetGear 1\n");
                    output.str("");
                    carHandler.HandleCommand();

                    THEN("the gear was switched on") {
                        CHECK(output.str() == "New gear has been switched on.\n");
                    }
                    
                    AND_WHEN("giving command SetSpeed") {
                        input.str("SetSpeed 30\n");
                        output.str("");
                        carHandler.HandleCommand();

                        THEN("the sheed was changed") {
                            CHECK(output.str() == "Speed has been changed.\n");
                        }

                        AND_WHEN("turning engine off") {
                            input.str("SetSpeed 0\nSetGear 0\nEngineOff\n");
                            output.str("");
                            carHandler.HandleCommand();
                            carHandler.HandleCommand();
                            carHandler.HandleCommand();
                            THEN("the engine was turned off") {
                                CHECK(output.str() == "Speed has been changed.\nNew gear has been switched on.\nCar's engine has been turned off.\n");
                            }
                        }
                    }
                }
            }
        }

        WHEN("giving command SetGear while the engine is off") {
            input.str("SetGear 2\nSetGear 3\nSetGear 4\nSetGear 5\nSetGear 6\nSetGear 2\nSetGear -2\n");
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            THEN("gear couldn't has been set when the engine was off") {
                std::string str1 = "New gear cannot be switched on. Only neutral gear can be switched to while car's engine is turned off.\n";
                std::string str2 = "New gear cannot be switched on. Gear number is out of range.\n";
                std::string expectedOutStr = str1 + str1 + str1 + str1 + str2 + str1 + str2;
                CHECK(output.str() == expectedOutStr);
            }
            AND_WHEN("giving command SetGear after turning engine on") {
                input.str("EngineOn\nSetGear 2\nSetGear 3\nSetGear 4\nSetGear 5\nSetGear 6\nSetGear 2\nSetGear -2\nSetGear -1\n");
                output.str("");
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();

                THEN("only reverse gear was set ") {
                    std::string str1 = "New gear cannot be switched on. Current speed is out of range of the new gear.\n";
                    std::string str2 = "New gear cannot be switched on. Gear number is out of range.\n";
                    std::string str3 = "New gear has been switched on.\n";
                    std::string str4 = "Car's engine has been turned on.\n";
                    std::string expectedOutStr = str4 + str1 + str1 + str1 + str1 + str2 + str1 + str2 + str3;
                    CHECK(output.str() == expectedOutStr);
                }

                AND_WHEN("trying to switch to the 1st gear riding with non zero speed") {
                    input.str("SetSpeed 15\nSetGear 1\n");
                    output.str("");
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();

                    THEN("unable to switch to forward gear from back gear until the car stops") {
                        CHECK(output.str() == "Speed has been changed.\nNew gear cannot be switched on. Forward gear can be switched to while riding on the back draft only after reducing speed to 0.\n");
                    }
                }
            }
            AND_WHEN("trying to switch to the back gear while riding forward") {
                input.str("EngineOn\nSetGear 1\nSetSpeed 10\nSetGear -1\n");
                output.str("");
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                THEN("unable to switch to back gear from forward gear until the car stops") {
                    CHECK(output.str() == "Car's engine has been turned on.\nNew gear has been switched on.\nSpeed has been changed.\nNew gear cannot be switched on. Reverse gear can be switched to if only car has 0 speed.\n");
                }
               
                AND_WHEN("trying to switch to another gear which is out of range") {
                    input.str("SetGear 2\nSetGear 3\nSetGear 4\nSetGear 5\n");
                    output.str("");
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();

                    THEN("unable to switch to another gear which is out of range") {
                        std::string str = "New gear cannot be switched on. Current speed is out of range of the new gear.\n";
                        std::string expectedOutStr = str + str + str + str;
                        CHECK(output.str() == expectedOutStr);
                    }
                }
            }
        }

        WHEN("giving command SetSpeed while the engine is off") {
            input.str("SetSpeed 10\nSetSpeed 20\nSetSpeed 30\nSetSpeed 40\n");
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            carHandler.HandleCommand();
            carHandler.HandleCommand();

            THEN("speed couldn't has been set when the engine was off") {
                std::string str = "Speed cannot be changed. The engine is turned off.\n";
                std::string expectedOutStr = str + str + str + str;
                CHECK(output.str() == expectedOutStr);
            }
            AND_WHEN("giving command SetGear after turning engine on") {
                input.str("EngineOn\nSetSpeed 10\nSetSpeed 20\nSetSpeed 30\nSetSpeed 40\nSetSpeed -10\n");
                output.str("");
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();
                carHandler.HandleCommand();

                THEN("speed cannot increase while the gear is 0") {
                    std::string str1 = "Car's engine has been turned on.\n";
                    std::string str2 = "Speed cannot be changed. Speed can only drop while the gear is neutral.\n";
                    std::string str3 = "Speed cannot be changed. Speed must be non negative number.\n";
                    std::string expectedOutStr = str1 + str2 + str2 + str2 + str2 + str3;
                    CHECK(output.str() == expectedOutStr);
                }

                AND_WHEN("trying to increase speed") {
                    input.str("SetGear 1\nSetSpeed 10\nSetSpeed 20\nSetSpeed 30\nSetSpeed 40\n");
                    output.str("");
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();
                    carHandler.HandleCommand();
                    THEN("able to increase speed until it's out of range") {
                        CHECK(output.str() == "New gear has been switched on.\nSpeed has been changed.\nSpeed has been changed.\nSpeed has been changed.\nSpeed cannot be changed. New speed is out of range.\n");
                    }
                }
            }
        }
    }
}
