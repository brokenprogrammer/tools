/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2017 Oskar Mendel
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
package me.oskarmendel.wordcount

import java.io.File

fun main(args : Array<String>) {
    if (args.isEmpty()) {
        println("Please enter a file path as a command-line argument!")
        return
    }

    if (isFilePath(args[0])) {
        val file = File(args[0])
        val content = file.readText()
        val words = getWords(content)
        val wordCounts = words.groupBy { it }.mapValues({ it.value.size })

        //
        // @hardcode @refactor Right now only hardcoded top three values.
        //

        var biggest = ""
        var second = ""
        var third = ""

        for ((word, count) in wordCounts) {
            if (biggest == "" || count > (wordCounts[(biggest)]!!)) {
                biggest = word
            } else if (second == "" || count > (wordCounts[(second)]!!)) {
                second = word
            } else if (third == "" || count > (wordCounts[(third)]!!)) {
                third = word
            }
        }

        println("Total words: " + words.size)
        println("1st most used word: " + biggest + " " + wordCounts[(biggest)])
        println("2nd most used word: " + second + " " + wordCounts[(second)])
        println("3rd most used word: " + third + " " + wordCounts[(third)])

    } else {
        print("Please enter a valid file path as a command-line argument!")
        return
    }
}

fun isFilePath(path: String) : Boolean {
    val f = File(path)

    return (f.isFile && !f.isDirectory)
}

fun getWords(content: String) : List<String> {
    //
    // @refactor check different file types and handle them differently.
    //
    return content.toLowerCase().replace(Regex("[^\\w']"), " ").trim().split(Regex("\\s+"))
}