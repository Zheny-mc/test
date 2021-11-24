package com.applicaton.Book.controllers;

import com.applicaton.Book.Model.dataBase.BookRepository;
import com.applicaton.Book.Model.entity.Book;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
public class BookConrol {

    @Autowired
    private BookRepository bookRepository;

    @GetMapping("get")
    public List<Book> getBooks() {
        List<Book> bookList = new ArrayList<>();
        bookRepository.findAll().forEach(bookList::add);
        return bookList;
    }

    @PostMapping("add_book")
    public void addBook(@RequestBody Book book) {
        bookRepository.save(book);
    }

    @PostMapping("del_book")
    public void delBook(@RequestBody Book book) {
        bookRepository.delete(book);
    }

    @PostMapping("del_all_book")
    public void del_all_Book() {
        bookRepository.deleteAll();
    }

}
