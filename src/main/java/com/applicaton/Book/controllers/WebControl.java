package com.applicaton.Book.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;


@Controller
public class WebControl {

    @GetMapping("main")
    public String toMain() {
        return "main";
    }

    @GetMapping("basket")
    public String toBasket() {
        return "basket";
    }


}