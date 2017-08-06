/**
 * Created by Oskar on 2017-08-05.
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

        val mostUsed : MutableList<String>

        //
        // @hardcode @refactor Right now only hardcoded top three values.
        //

        var biggest = ""
        var second = ""
        var third = ""

        for (entry in wordCounts) {
            val word = entry.key
            val count = entry.value

            if (biggest == null || biggest == "" || count.compareTo(wordCounts.get(biggest)!!) > 0) {
                biggest = word
            } else if ((second == null || second == "" || count.compareTo(wordCounts.get(second)!!) > 0)) {
                second = word
            } else if ((third == null || third == "" || count.compareTo(wordCounts.get(third)!!) > 0)) {
                third = word
            }
        }

        println("Total words: " + words.size)
        println("1st most used word: " + biggest + " " + wordCounts.get(biggest))
        println("2nd most used word: " + second + " " + wordCounts.get(second))
        println("3rd most used word: " + third + " " + wordCounts.get(third))

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