package com.applicaton.Book.Model.entity;

import lombok.*;

import javax.persistence.*;
import java.io.Serializable;

@Entity
@Table(name = "book")
@Getter
@Setter
@ToString
@AllArgsConstructor
@NoArgsConstructor
public class Book implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String title;
    private String author;
    private Integer price;
    @Column(name="ref_img")
    private String refImg;
    @Column(name = "is_record")
    private Boolean isRecord;
}
