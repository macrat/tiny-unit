/** Tiny and easy unit test.
 *
 * @file
 */

#ifndef __TINY_UNIT_TEST_H__
#define __TINY_UNIT_TEST_H__

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>


/** Tiny and easy unit test package. */
namespace TinyUnit {

/** Set of some tests. Like a test suite. */
class Test {
private:
    int count;          ///< Number of done tests.
    int success;        ///< Number of successful tests.
    std::ostream& out;  ///< Output stream for write message.


    /** One of test case.
     *
     * Case hasn't setup and teardown.
     */
    class Case {
    private:
        Test& parent;            ///< Reference to parent Test.
        const std::string name;  ///< Name of this test case.


        /** Mark result into parent Test.
         *
         * @param result  If true, write as success. Otherwise write as failed.
         */
        void mark(bool result) {
            parent.count++;
            parent.success += result;
        }

        /** Show successful message. */
        template <class T> void show_success(T message) {
            parent.out << "\r\e[37m" << name << "\e[0m[\e[32m" << std::setw(4) << message << "\e[0m]" << std::endl;
        }

        /** Show failed message. */
        template <class T> void show_fail(T message) {
            parent.out << "\r\e[41;37m" << name << "[" << std::setw(4) << message << "]\e[0m" << std::endl;
        }

        /** Mark result into parent Test and show message that successful or failed.
         *
         * @param result  If true, write as success and show successful message. Otherwise, will do opposite.
         */
        template <class T> void mark_and_show(bool result, T message) {
            mark(result);

            if(result){
                show_success(message);
            }else{
                show_fail(message);
            }
        }

    public:
        /** construct
         *
         * User can't construct this class without TinyUnit::Test::case_
         *
         * @param parent  Reference to parent Test.
         * @param name    Name of this Case.
         */
        Case(Test& parent, std::string name) : parent(parent), name(name + std::string(std::max(0ul, 60ul - name.length()), ' ')) {
            parent.out << this->name << "\e[37m[...]\e[0m" << std::flush;
        }

        /** Confirm given value is true.
         *
         * Show "OK" as green color if given value is true, otherwise "FAIL" as red color.
         */
        Test& assert(bool v) {
            mark(v);

            if(v){
                show_success(" OK ");
            }else{
                show_fail("FAIL");
            }

            return parent;
        }

        /** Confirm given values equals.
         *
         * Show value as green color if given values is equals. Otherwise, show value as red color.
         *
         * You can use any types that can use == operator for this method.
         */
        template <class T, class U> Test& equals(T x, U y) {
            std::ostringstream buf;
            buf << x << " == " << y;

            mark_and_show(x == y, buf.str());

            return parent;
        }

        /** Confirm given values isn't equals.
         *
         * Show value as green color if given values isn't equals. Otherwise, show value as red color.
         *
         * You can use any types that can use != operator for this method.
         */
        template <class T, class U> Test& not_equals(T x, U y) {
            std::ostringstream buf;
            buf << x << " != " << y;

            mark_and_show(x != y, buf.str());

            return parent;
        }

        /** Confirm given two values order.
         *
         * Show value as green color if given x is less than y. Otherwise, show value as red color.
         *
         * You can use any types that can use < operator for this method.
         */
        template <class T, class U> Test& less(T x, U y) {
            std::ostringstream buf;
            buf << x << " < " << y;

            mark_and_show(x < y, buf.str());

            return parent;
        }

        /** Confirm given three values order.
         *
         * Show value as green color if given x is less than y and y is less than z. Otherwise, show value as red color.
         *
         * You can use any types that can use < operator for this method.
         */
        template <class T, class U, class V> Test& less(T x, U y, V z) {
            std::ostringstream buf;
            buf << x << " < " << y << " < " << z;

            mark_and_show(x < y && y < z, buf.str());

            return parent;
        }
    };


public:
    /** Initialize
     *
     * Output for stdout.
     */
    Test() : out(std::cout) {
        count = success = 0;
    }

    /** Initialize
     *
     * @param out  Output stream for write message.
     */
    Test(std::ostream& out) : out(out) {
        count = success = 0;
    }

    /** Make new Case.
     *
     * @param name  Name of new test case. Recommend to shorter than 59 characters.
     */
    Case case_(std::string name) {
        return Case(*this, name);
    }

    /** Get number of done tests. */
    int getCount() {
        return count;
    }

    /** Get number of successful tests. */
    int getSuccessCount() {
        return success;
    }

    /** Show statistics report. */
    void show_report() {
        out << std::endl;
        if(success == count){
            out << count << " tests was done, and \e[32mall successful\e[0m." << std::endl;
        }else{
            out << count << " tests was done." << std::endl;
            out << "\e[32m" << success << " tests\e[0m was successful, and \e[31m" << (count - success) << " tests\e[0m was failed." << std::endl;
        }
    }
};

};

#endif
