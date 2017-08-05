/**
 * Created by Oskar on 2017-08-05.
 */
package me.oskarmendel.wordcount

import java.io.File

fun main(args : Array<String>) {
    if (args.size == 0) {
        println("Please enter a file path as a command-line argument!")
        return
    }

    if (isFilePath(args[0])) {
        println("Valid File.")
    } else {
        print("Please enter a valid file path as a command-line argument!")
        return
    }
}

fun isFilePath(path: String) : Boolean {
    val f = File(path)

    if (f.isFile() && !f.isDirectory()) {
        return true
    } else {
        return false
    }
}