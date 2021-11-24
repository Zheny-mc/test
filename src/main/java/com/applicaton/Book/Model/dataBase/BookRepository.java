package com.applicaton.Book.Model.dataBase;

import com.applicaton.Book.Model.entity.Book;
import org.springframework.data.repository.CrudRepository;

public interface BookRepository extends CrudRepository<Book, Long> {
}
