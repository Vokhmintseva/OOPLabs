#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include <iostream>
#include "../Car/Car.h"
#include "../Car/CarHandler.h"

SCENARIO("car") {

    GIVEN("car") {
        
        Car car;
       
        THEN("State after initialization") {
            REQUIRE(car.IsTurnedOn() == false);
            REQUIRE(car.GetDirection() == "static");
            REQUIRE(car.GetSpeed() == 0);
            REQUIRE(car.GetGear() == 0);
        }
        
        WHEN("turning engine on") {
            car.TurnOnEngine();

            THEN("engine is turned on") {
                REQUIRE(car.IsTurnedOn() == true);
                REQUIRE(car.GetDirection() == "static");
                REQUIRE(car.GetSpeed() == 0);
                REQUIRE(car.GetGear() == 0);
            }
            AND_WHEN("setting gear to 1") {
                car.SetGear(1);
                THEN("engine is turned on and the gear is 1") {
                    REQUIRE(car.IsTurnedOn() == true);
                    REQUIRE(car.GetDirection() == "static");
                    REQUIRE(car.GetSpeed() == 0);
                    REQUIRE(car.GetGear() == 1);
                }

                AND_WHEN("engine is turned on, the gear is 1 and speed is 30") {
                    car.SetSpeed(30);
                    THEN("the size and capacity change") {
                        REQUIRE(car.IsTurnedOn() == true);
                        REQUIRE(car.GetDirection() == "forward");
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
                        REQUIRE(car.GetDirection() == "forward");
                        REQUIRE(car.GetSpeed() == 30);
                        REQUIRE(car.GetGear() == 1);
                    }
                }
            }
        }
    }
}