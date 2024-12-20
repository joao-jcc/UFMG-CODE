import React, { Component } from 'react';
import CalendarDays from './CalendarDays';


export default class Calendar extends Component  {
    constructor() {
        super();

        this.weekdays = ['Sun', 'Mon', 'Tue', 'Wed', 'Thu', 'Fri', 'Sat'];
        this.months = ['January', 'February', 'March', 'April', 'May', 'June',
          'July', 'August', 'September', 'October', 'November', 'December'];
        
        this.currentDay = new Date();
    }

    changeCurrentDay = (day) => {
        this.currentDay = day;
    }

    nextDay = () => {
        this.currentDay.setDate(this.currentDay.getDate() + 1);
    }

    previousDay = () => {
        this.currentDay.setDate(this.currentDay.getDate() - 1);
    }

    focusToday = () => {

    }


    render() {
        return (
            <div className="calendar">
                <div className="calendar-header">
                    <div className="title">
                        <h2>{this.months[this.currentDay.getMonth()]} {this.currentDay.getFullYear()}</h2>
                    </div>
                    <div className="tools">
                        <button onClick={this.previousDay}>
                            <span className="material-icons">
                            arrow_back
                            </span>
                        </button>

                        <button onClick={this.focusToday}>
                            Today
                        </button>

                        <button onClick={this.nextDay}>
                            <span className="material-icons">
                            arrow_forward
                            </span>
                        </button>
                    </div>
                </div>

                <div className="calendar-body">
                    <div className="table-header">
                        {
                        this.weekdays.map((weekday) => {
                            return <div className="weekday"><p>{weekday}</p></div>
                        })
                        }
                    </div>
                    <CalendarDays day={this.currentDay} changeCurrentDay={this.changeCurrentDay} />
                </div>

          </div>
        )
    }
}
